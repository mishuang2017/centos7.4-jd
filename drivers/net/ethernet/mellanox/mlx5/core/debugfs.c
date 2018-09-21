/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/mlx5/qp.h>
#include <linux/mlx5/qp_exp.h>
#include <linux/mlx5/cq.h>
#include <linux/mlx5/driver.h>
#include "mlx5_core.h"
#include "vxlan.h"

enum {
	QP_PID,
	QP_STATE,
	QP_XPORT,
	QP_MTU,
	QP_N_RECV,
	QP_RECV_SZ,
	QP_N_SEND,
	QP_LOG_PG_SZ,
	QP_RQPN,
};

static char *qp_fields[] = {
	[QP_PID]	= "pid",
	[QP_STATE]	= "state",
	[QP_XPORT]	= "transport",
	[QP_MTU]	= "mtu",
	[QP_N_RECV]	= "num_recv",
	[QP_RECV_SZ]	= "rcv_wqe_sz",
	[QP_N_SEND]	= "num_send",
	[QP_LOG_PG_SZ]	= "log2_page_sz",
	[QP_RQPN]	= "remote_qpn",
};

enum {
	DCT_PID,
	DCT_STATE,
	DCT_MTU,
	DCT_KEY_VIOL,
	DCT_CQN,
};

static char *dct_fields[] = {
	[DCT_PID]	= "pid",
	[DCT_STATE]	= "state",
	[DCT_MTU]	= "mtu",
	[DCT_KEY_VIOL]	= "key_violations",
	[DCT_CQN]	= "cqn",
};

enum {
	EQ_NUM_EQES,
	EQ_INTR,
	EQ_LOG_PG_SZ,
};

static char *eq_fields[] = {
	[EQ_NUM_EQES]	= "num_eqes",
	[EQ_INTR]	= "intr",
	[EQ_LOG_PG_SZ]	= "log_page_size",
};

enum {
	CQ_PID,
	CQ_NUM_CQES,
	CQ_LOG_PG_SZ,
};

static char *cq_fields[] = {
	[CQ_PID]	= "pid",
	[CQ_NUM_CQES]	= "num_cqes",
	[CQ_LOG_PG_SZ]	= "log_page_size",
};

struct dentry *mlx5_debugfs_root;
EXPORT_SYMBOL(mlx5_debugfs_root);

void mlx5_register_debugfs(void)
{
	mlx5_debugfs_root = debugfs_create_dir("mlx5", NULL);
	if (IS_ERR_OR_NULL(mlx5_debugfs_root))
		mlx5_debugfs_root = NULL;
}

void mlx5_unregister_debugfs(void)
{
	debugfs_remove(mlx5_debugfs_root);
}

int mlx5_qp_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	atomic_set(&dev->num_qps, 0);

	dev->priv.qp_debugfs = debugfs_create_dir("QPs",  dev->priv.dbg_root);
	if (!dev->priv.qp_debugfs)
		return -ENOMEM;

	return 0;
}

void mlx5_qp_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove_recursive(dev->priv.qp_debugfs);
}

int mlx5_dct_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	dev->priv.dct_debugfs = debugfs_create_dir("DCTs",  dev->priv.dbg_root);
	if (!dev->priv.dct_debugfs)
		return -ENOMEM;

	return 0;
}

void mlx5_dct_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove_recursive(dev->priv.dct_debugfs);
}

int mlx5_eq_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	dev->priv.eq_debugfs = debugfs_create_dir("EQs",  dev->priv.dbg_root);
	if (!dev->priv.eq_debugfs)
		return -ENOMEM;

	return 0;
}

void mlx5_eq_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove_recursive(dev->priv.eq_debugfs);
}

int mlx5_vxlan_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	dev->priv.vxlan_debugfs = debugfs_create_dir("VXLAN",
						     dev->priv.dbg_root);

	return dev->priv.vxlan_debugfs ? 0 : -ENOMEM;
}

void mlx5_vxlan_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove_recursive(dev->priv.vxlan_debugfs);
}

int mlx5_vxlan_debugfs_add(struct mlx5_core_dev *dev,
			   struct mlx5e_vxlan *vxlan)
{
	char resn[32];

	if (!mlx5_debugfs_root)
		return 0;

	sprintf(resn, "%d", vxlan->udp_port);
	vxlan->dbg = debugfs_create_u16(resn, 0400, dev->priv.vxlan_debugfs,
					&vxlan->udp_port);

	return vxlan->dbg ? 0 : -ENOMEM;
}

void mlx5_vxlan_debugfs_remove(struct mlx5_core_dev *dev,
			       struct mlx5e_vxlan *vxlan)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove(vxlan->dbg);
}

static ssize_t average_read(struct file *filp, char __user *buf, size_t count,
			    loff_t *pos)
{
	struct mlx5_cmd_stats *stats;
	u64 field = 0;
	int ret;
	char tbuf[22];

	if (*pos)
		return 0;

	stats = filp->private_data;
	spin_lock_irq(&stats->lock);
	if (stats->n)
		field = div64_u64(stats->sum, stats->n);
	spin_unlock_irq(&stats->lock);
	ret = snprintf(tbuf, sizeof(tbuf), "%llu\n", field);
	if (ret > 0) {
		if (copy_to_user(buf, tbuf, ret))
			return -EFAULT;
	}

	*pos += ret;
	return ret;
}

static ssize_t average_write(struct file *filp, const char __user *buf,
			     size_t count, loff_t *pos)
{
	struct mlx5_cmd_stats *stats;

	stats = filp->private_data;
	spin_lock_irq(&stats->lock);
	stats->sum = 0;
	stats->n = 0;
	spin_unlock_irq(&stats->lock);

	*pos += count;

	return count;
}

static const struct file_operations stats_fops = {
	.owner	= THIS_MODULE,
	.open	= simple_open,
	.read	= average_read,
	.write	= average_write,
};

int mlx5_cmdif_debugfs_init(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd_stats *stats;
	struct dentry **cmd;
	const char *namep;
	int err;
	int i;

	if (!mlx5_debugfs_root)
		return 0;

	cmd = &dev->priv.cmdif_debugfs;
	*cmd = debugfs_create_dir("commands", dev->priv.dbg_root);
	if (!*cmd)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(dev->cmd.stats); i++) {
		stats = &dev->cmd.stats[i];
		namep = mlx5_command_str(i);
		if (strcmp(namep, "unknown command opcode")) {
			stats->root = debugfs_create_dir(namep, *cmd);
			if (!stats->root) {
				mlx5_core_warn(dev, "failed adding command %d\n",
					       i);
				err = -ENOMEM;
				goto out;
			}

			stats->avg = debugfs_create_file("average", 0400,
							 stats->root, stats,
							 &stats_fops);
			if (!stats->avg) {
				mlx5_core_warn(dev, "failed creating debugfs file\n");
				err = -ENOMEM;
				goto out;
			}

			stats->count = debugfs_create_u64("n", 0400,
							  stats->root,
							  &stats->n);
			if (!stats->count) {
				mlx5_core_warn(dev, "failed creating debugfs file\n");
				err = -ENOMEM;
				goto out;
			}
		}
	}

	return 0;
out:
	debugfs_remove_recursive(dev->priv.cmdif_debugfs);
	dev->priv.cmdif_debugfs = NULL;
	return err;
}

void mlx5_cmdif_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root || !dev->priv.cmdif_debugfs)
		return;

	debugfs_remove_recursive(dev->priv.cmdif_debugfs);
}

int mlx5_cq_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	dev->priv.cq_debugfs = debugfs_create_dir("CQs",  dev->priv.dbg_root);
	if (!dev->priv.cq_debugfs)
		return -ENOMEM;

	return 0;
}

void mlx5_cq_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return;

	debugfs_remove_recursive(dev->priv.cq_debugfs);
}

static u64 qp_read_field(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp,
			 int index, int *is_str)
{
	int outlen = MLX5_ST_SZ_BYTES(query_qp_out);
	struct mlx5_qp_context *ctx;
	u64 param = 0;
	u32 *out;
	int err;
	int no_sq;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_qp_query(dev, qp, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query qp err=%d\n", err);
		goto out;
	}

	*is_str = 0;

	/* FIXME: use MLX5_GET rather than mlx5_qp_context manual struct */
	ctx = (struct mlx5_qp_context *)MLX5_ADDR_OF(query_qp_out, out, qpc);

	switch (index) {
	case QP_PID:
		param = qp->pid;
		break;
	case QP_STATE:
		param = (unsigned long)mlx5_qp_state_str(be32_to_cpu(ctx->flags) >> 28);
		*is_str = 1;
		break;
	case QP_XPORT:
		param = (unsigned long)mlx5_qp_type_str((be32_to_cpu(ctx->flags) >> 16) & 0xff);
		*is_str = 1;
		break;
	case QP_MTU:
		switch (ctx->mtu_msgmax >> 5) {
		case IB_MTU_256:
			param = 256;
			break;
		case IB_MTU_512:
			param = 512;
			break;
		case IB_MTU_1024:
			param = 1024;
			break;
		case IB_MTU_2048:
			param = 2048;
			break;
		case IB_MTU_4096:
			param = 4096;
			break;
		default:
			param = 0;
		}
		break;
	case QP_N_RECV:
		param = 1 << ((ctx->rq_size_stride >> 3) & 0xf);
		break;
	case QP_RECV_SZ:
		param = 1 << ((ctx->rq_size_stride & 7) + 4);
		break;
	case QP_N_SEND:
		no_sq = be16_to_cpu(ctx->sq_crq_size) >> 15;
		if (!no_sq)
			param = 1 << (be16_to_cpu(ctx->sq_crq_size) >> 11);
		else
			param = 0;
		break;
	case QP_LOG_PG_SZ:
		param = (be32_to_cpu(ctx->log_pg_sz_remote_qpn) >> 24) & 0x1f;
		param += 12;
		break;
	case QP_RQPN:
		param = be32_to_cpu(ctx->log_pg_sz_remote_qpn) & 0xffffff;
		break;
	}

out:
	kfree(out);
	return param;
}

static u64 dct_read_field(struct mlx5_core_dev *dev, struct mlx5_core_dct *dct,
			  int index, int *is_str)
{
	u32 *out;
	int outlen =  MLX5_ST_SZ_BYTES(query_dct_out);
	void *dctc;
	u64 param = 0;
	int err;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_dct_query(dev, dct, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query dct\n");
		goto out;
	}

	dctc = MLX5_ADDR_OF(query_dct_out, out, dct_context_entry);
	*is_str = 0;
	switch (index) {
	case DCT_PID:
		param = dct->pid;
		break;
	case DCT_STATE:
		param = (u64)mlx5_dct_state_str(MLX5_GET(dctc, dctc, state));
		*is_str = 1;
		break;
	case DCT_MTU:
		param = MLX5_GET(dctc, dctc, mtu);
		break;
	case DCT_KEY_VIOL:
		param = MLX5_GET(dctc, dctc, dc_access_key_violation_count);
		break;
	case DCT_CQN:
		param = MLX5_GET(dctc, dctc, cqn);
		break;
	}

out:
	kfree(out);
	return param;
}

static u64 eq_read_field(struct mlx5_core_dev *dev, struct mlx5_eq *eq,
			 int index)
{
	int outlen = MLX5_ST_SZ_BYTES(query_eq_out);
	u64 param = 0;
	void *ctx;
	u32 *out;
	int err;

	out = kzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_eq_query(dev, eq, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query eq\n");
		goto out;
	}
	ctx = MLX5_ADDR_OF(query_eq_out, out, eq_context_entry);

	switch (index) {
	case EQ_NUM_EQES:
		param = 1 << MLX5_GET(eqc, ctx, log_eq_size);
		break;
	case EQ_INTR:
		param = MLX5_GET(eqc, ctx, intr);
		break;
	case EQ_LOG_PG_SZ:
		param = MLX5_GET(eqc, ctx, log_page_size) + 12;
		break;
	}

out:
	kfree(out);
	return param;
}

static u64 cq_read_field(struct mlx5_core_dev *dev, struct mlx5_core_cq *cq,
			 int index)
{
	int outlen = MLX5_ST_SZ_BYTES(query_cq_out);
	u64 param = 0;
	void *ctx;
	u32 *out;
	int err;

	out = kvzalloc(outlen, GFP_KERNEL);
	if (!out)
		return param;

	err = mlx5_core_query_cq(dev, cq, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "failed to query cq\n");
		goto out;
	}
	ctx = MLX5_ADDR_OF(query_cq_out, out, cq_context);

	switch (index) {
	case CQ_PID:
		param = cq->pid;
		break;
	case CQ_NUM_CQES:
		param = 1 << MLX5_GET(cqc, ctx, log_cq_size);
		break;
	case CQ_LOG_PG_SZ:
		param = MLX5_GET(cqc, ctx, log_page_size);
		break;
	}

out:
	kvfree(out);
	return param;
}

static ssize_t dbg_read(struct file *filp, char __user *buf, size_t count,
			loff_t *pos)
{
	struct mlx5_field_desc *desc;
	struct mlx5_rsc_debug *d;
	char tbuf[18];
	int is_str = 0;
	u64 field;
	int ret;

	if (*pos)
		return 0;

	desc = filp->private_data;
	d = (void *)(desc - desc->i) - sizeof(*d);
	switch (d->type) {
	case MLX5_DBG_RSC_QP:
		field = qp_read_field(d->dev, d->object, desc->i, &is_str);
		break;

	case MLX5_DBG_RSC_EQ:
		field = eq_read_field(d->dev, d->object, desc->i);
		break;

	case MLX5_DBG_RSC_CQ:
		field = cq_read_field(d->dev, d->object, desc->i);
		break;

	case MLX5_DBG_RSC_DCT:
		field = dct_read_field(d->dev, d->object, desc->i, &is_str);
		break;

	default:
		mlx5_core_warn(d->dev, "invalid resource type %d\n", d->type);
		return -EINVAL;
	}

	if (is_str)
		ret = snprintf(tbuf, sizeof(tbuf), "%s\n", (const char *)(unsigned long)field);
	else
		ret = snprintf(tbuf, sizeof(tbuf), "0x%llx\n", field);

	if (ret > 0) {
		if (copy_to_user(buf, tbuf, ret))
			return -EFAULT;
	}

	*pos += ret;
	return ret;
}

static const struct file_operations fops = {
	.owner	= THIS_MODULE,
	.open	= simple_open,
	.read	= dbg_read,
};

static int add_res_tree(struct mlx5_core_dev *dev, enum dbg_rsc_type type,
			struct dentry *root, struct mlx5_rsc_debug **dbg,
			int rsn, char **field, int nfile, void *data)
{
	struct mlx5_rsc_debug *d;
	char resn[32];
	int err;
	int i;

	d = kzalloc(sizeof(*d) + nfile * sizeof(d->fields[0]), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->dev = dev;
	d->object = data;
	d->type = type;
	sprintf(resn, "0x%x", rsn);
	d->root = debugfs_create_dir(resn,  root);
	if (!d->root) {
		err = -ENOMEM;
		goto out_free;
	}

	for (i = 0; i < nfile; i++) {
		d->fields[i].i = i;
		d->fields[i].dent = debugfs_create_file(field[i], 0400,
							d->root, &d->fields[i],
							&fops);
		if (!d->fields[i].dent) {
			err = -ENOMEM;
			goto out_rem;
		}
	}
	*dbg = d;

	return 0;
out_rem:
	debugfs_remove_recursive(d->root);

out_free:
	kfree(d);
	return err;
}

static void rem_res_tree(struct mlx5_rsc_debug *d)
{
	debugfs_remove_recursive(d->root);
	kfree(d);
}

int mlx5_debug_qp_add(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_QP, dev->priv.qp_debugfs,
			   &qp->dbg, qp->qpn, qp_fields,
			   ARRAY_SIZE(qp_fields), qp);
	if (err)
		qp->dbg = NULL;

	return err;
}

void mlx5_debug_qp_remove(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp)
{
	if (!mlx5_debugfs_root)
		return;

	if (qp->dbg)
		rem_res_tree(qp->dbg);
}

int mlx5_debug_dct_add(struct mlx5_core_dev *dev, struct mlx5_core_dct *dct)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_DCT, dev->priv.dct_debugfs,
			   &dct->dbg, dct->dctn, dct_fields,
			   ARRAY_SIZE(dct_fields), dct);
	if (err)
		dct->dbg = NULL;

	return err;
}

void mlx5_debug_dct_remove(struct mlx5_core_dev *dev, struct mlx5_core_dct *dct)
{
	if (!mlx5_debugfs_root)
		return;

	if (dct->dbg)
		rem_res_tree(dct->dbg);
}

int mlx5_debug_eq_add(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_EQ, dev->priv.eq_debugfs,
			   &eq->dbg, eq->eqn, eq_fields,
			   ARRAY_SIZE(eq_fields), eq);
	if (err)
		eq->dbg = NULL;

	return err;
}

void mlx5_debug_eq_remove(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	if (!mlx5_debugfs_root)
		return;

	if (eq->dbg)
		rem_res_tree(eq->dbg);
}

int mlx5_debug_cq_add(struct mlx5_core_dev *dev, struct mlx5_core_cq *cq)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_CQ, dev->priv.cq_debugfs,
			   &cq->dbg, cq->cqn, cq_fields,
			   ARRAY_SIZE(cq_fields), cq);
	if (err)
		cq->dbg = NULL;

	return err;
}

void mlx5_debug_cq_remove(struct mlx5_core_dev *dev, struct mlx5_core_cq *cq)
{
	if (!mlx5_debugfs_root)
		return;

	if (cq->dbg)
		rem_res_tree(cq->dbg);
}

void mlx5_offloaded_stats_debugfs_cleanup(struct mlx5_core_dev *dev)
{
	debugfs_remove_recursive(dev->priv.dbg_offloaded_stats);
	dev->priv.dbg_offloaded_stats = NULL;
}

int mlx5_offloaded_stats_debugfs_init(struct mlx5_core_dev *dev)
{
	struct dentry *dbg_root = dev->priv.dbg_root;
	struct mlx5_priv *priv = &dev->priv;

	dev->offloaded_stats = true;

	if (!mlx5_debugfs_root)
		return 0;

	priv->dbg_offloaded_stats = debugfs_create_bool("offloaded_stats",
							0600, dbg_root,
							&dev->offloaded_stats);
	if (!priv->dbg_offloaded_stats)
		return -ENOMEM;

	return 0;
}
