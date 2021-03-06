#ifndef __OFED_BUILD__
#include_next <generated/autoconf.h>


















/* CONFIG_SUNRPC_XPRT_RDMA is not set */
/* CONFIG_SUNRPC_XPRT_RDMA_DUMMY is not set */


















#define CONFIG_MLX5_CORE 1
#define CONFIG_MLX5_CORE_EN 1
#define CONFIG_MLX5_CORE_EN_DCB 1
#define CONFIG_MLX5_MPFS 1
#define CONFIG_MLX5_ESWITCH 1

#define CONFIG_MLX5_INNER_RSS 1
#define CONFIG_MLX5_EN_SPECIAL_SQ 1






#define CONFIG_MLX5_DEBUG 1






















#define CONFIG_INFINIBAND_ON_DEMAND_PAGING 1




#else
#undef CONFIG_COMPAT_VERSION
#undef CONFIG_MEMTRACK
#undef CONFIG_DEBUG_INFO
#undef CONFIG_INFINIBAND
#undef CONFIG_INFINIBAND_CORE_DUMMY
#undef CONFIG_INFINIBAND_IPOIB
#undef CONFIG_INFINIBAND_IPOIB_CM
#undef CONFIG_IPOIB_ALL_MULTI
#undef CONFIG_INFINIBAND_SRP
#undef CONFIG_INFINIBAND_SRP_DUMMY

#undef CONFIG_CONFIG_RDMA_RXE
#undef CONFIG_CONFIG_RDMA_RXE_DUMMY

#undef CONFIG_INFINIBAND_USER_MAD
#undef CONFIG_INFINIBAND_USER_ACCESS
#undef CONFIG_INFINIBAND_USER_ACCESS_UCM
#undef CONFIG_INFINIBAND_ADDR_TRANS
#undef CONFIG_INFINIBAND_ADDR_TRANS_CONFIGFS
#undef CONFIG_INFINIBAND_USER_MEM

#undef CONFIG_MLX4_CORE
#undef CONFIG_MLXFW
#undef CONFIG_MLX5_ACCEL
#undef CONFIG_MLX5_EN_TLS
#undef CONFIG_MLX5_EN_IPSEC
#undef CONFIG_MLX5_FPGA
#undef CONFIG_MLX5_FPGA_TOOLS
#undef CONFIG_MLX5_CORE
#undef CONFIG_MLX5_CORE_EN
#undef CONFIG_MLX5_CORE_EN_DCB
#undef CONFIG_MLX5_MPFS
#undef CONFIG_MLX5_ESWITCH
#undef CONFIG_MLX5_CORE_IPOIB
#undef CONFIG_MLX5_INNER_RSS
#undef CONFIG_MLX5_EN_SPECIAL_SQ
#undef CONFIG_MLX4_DEBUG
#undef CONFIG_MLX5_DEBUG
#undef CONFIG_MLX4_EN
#undef CONFIG_MLX4_EN_DCB
#undef CONFIG_MLX4_IB_DEBUG_FS
#undef CONFIG_MLX4_INFINIBAND
#undef CONFIG_MLX5_INFINIBAND
#undef CONFIG_BACKPORT_LRO

#undef CONFIG_MLX4_FC

#undef CONFIG_INFINIBAND_IPOIB_DEBUG
#undef CONFIG_INFINIBAND_ISER
#undef CONFIG_INFINIBAND_ISER_DUMMY
#undef CONFIG_INFINIBAND_ISERT
#undef CONFIG_INFINIBAND_ISERT_DUMMY
#undef CONFIG_INFINIBAND_MADEYE
#undef CONFIG_NVME_CORE
#undef CONFIG_NVME_HOST_WITHOUT_FC
#undef CONFIG_BLK_DEV_NVME
#undef CONFIG_NVME_FABRICS
#undef CONFIG_NVME_FC
#undef CONFIG_NVME_RDMA
#undef CONFIG_NVME_MULTIPATH
#undef CONFIG_NVME_HOST_DUMMY
#undef CONFIG_NVME_TARGET
#undef CONFIG_NVME_TARGET_LOOP
#undef CONFIG_NVME_TARGET_RDMA
#undef CONFIG_NVME_TARGET_FC
#undef CONFIG_NVME_TARGET_FCLOOP
#undef CONFIG_NVME_TARGET_DUMMY
#undef CONFIG_MLX4_EN_PERF_STAT

#undef CONFIG_SUNRPC_XPRT_RDMA
#undef CONFIG_SUNRPC_XPRT_RDMA_DUMMY

#undef CONFIG_SCSI_SRP_ATTRS

#undef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
#undef CONFIG_INFINIBAND_SDP_SEND_ZCOPY
#undef CONFIG_INFINIBAND_SDP_RECV_ZCOPY
#undef CONFIG_INFINIBAND_SDP_DEBUG
#undef CONFIG_INFINIBAND_SDP_DEBUG_DATA
#undef CONFIG_MLX4_EN_DCB
#undef CONFIG_MLX4_EN_PERF_STAT
#undef CONFIG_MLX4_IB_DEBUG_FS
#undef CONFIG_E_IPOIB

#undef CONFIG_INFINIBAND
#undef CONFIG_INFINIBAND_CORE_DUMMY
#undef CONFIG_INFINIBAND_IPOIB
#undef CONFIG_INFINIBAND_IPOIB_CM
#undef CONFIG_IPOIB_ALL_MULTI
#undef CONFIG_INFINIBAND_SRP
#undef CONFIG_INFINIBAND_SRP_DUMMY

#undef CONFIG_RDMA_RXE
#undef CONFIG_RDMA_RXE_DUMMY

#undef CONFIG_INFINIBAND_USER_MAD
#undef CONFIG_INFINIBAND_USER_ACCESS
#undef CONFIG_INFINIBAND_USER_ACCESS_UCM
#undef CONFIG_INFINIBAND_ADDR_TRANS
#undef CONFIG_INFINIBAND_ADDR_TRANS_CONFIGFS
#undef CONFIG_INFINIBAND_USER_MEM

/* CONFIG_SUNRPC_XPRT_RDMA is not set */
/* CONFIG_SUNRPC_XPRT_RDMA_DUMMY is not set */



#undef CONFIG_INFINIBAND_IPOIB_DEBUG
#undef CONFIG_INFINIBAND_ISERT
#undef CONFIG_INFINIBAND_ISERT_DUMMY
#undef CONFIG_INFINIBAND_ISER
#undef CONFIG_INFINIBAND_ISER_DUMMY
#undef CONFIG_SCSI_ISCSI_ATTRS
#undef CONFIG_ISCSI_TCP
#undef CONFIG_E_IPOIB
#undef CONFIG_MLX4_CORE
#undef CONFIG_MLXFW
#undef CONFIG_MLX5_ACCEL
#undef CONFIG_MLX5_EN_TLS
#undef CONFIG_MLX5_EN_IPSEC
#undef CONFIG_MLX5_FPGA
#undef CONFIG_MLX5_FPGA_TOOLS
#undef CONFIG_MLX5_CORE
#define CONFIG_MLX5_CORE 1
#undef CONFIG_MLX5_CORE_EN
#define CONFIG_MLX5_CORE_EN 1
#undef CONFIG_MLX5_CORE_EN_DCB
#define CONFIG_MLX5_CORE_EN_DCB 1
#undef CONFIG_MLX5_MPFS
#define CONFIG_MLX5_MPFS 1
#undef CONFIG_MLX5_ESWITCH
#define CONFIG_MLX5_ESWITCH 1
#undef CONFIG_MLX5_CORE_IPOIB
#undef CONFIG_MLX5_INNER_RSS
#define CONFIG_MLX5_INNER_RSS 1
#undef CONFIG_MLX5_EN_SPECIAL_SQ
#define CONFIG_MLX5_EN_SPECIAL_SQ 1
#undef CONFIG_MLX4_EN
#undef CONFIG_MLX4_IB_DEBUG_FS
#undef CONFIG_MLX4_INFINIBAND
#undef CONFIG_MLX5_INFINIBAND

#undef CONFIG_MLX4_DEBUG
#undef CONFIG_MLX5_DEBUG
#define CONFIG_MLX5_DEBUG 1
#undef CONFIG_MLX4_EN_PERF_STAT

#undef CONFIG_MLX4_FC

#undef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
#undef CONFIG_INFINIBAND_SDP_SEND_ZCOPY
#undef CONFIG_INFINIBAND_SDP_RECV_ZCOPY
#undef CONFIG_INFINIBAND_SDP_DEBUG
#undef CONFIG_INFINIBAND_SDP_DEBUG_DATA
#undef CONFIG_NVME_CORE
#undef CONFIG_NVME_HOST_WITHOUT_FC
#undef CONFIG_BLK_DEV_NVME
#undef CONFIG_NVME_FABRICS
#undef CONFIG_NVME_FC
#undef CONFIG_NVME_RDMA
#undef CONFIG_NVME_MULTIPATH
#undef CONFIG_NVME_HOST_DUMMY
#undef CONFIG_NVME_TARGET
#undef CONFIG_NVME_TARGET_LOOP
#undef CONFIG_NVME_TARGET_RDMA
#undef CONFIG_NVME_TARGET_FC
#undef CONFIG_NVME_TARGET_FCLOOP
#undef CONFIG_NVME_TARGET_DUMMY
#undef CONFIG_INFINIBAND_MADEYE
#undef CONFIG_MLX4_EN_DCB



#undef CONFIG_INFINIBAND_ON_DEMAND_PAGING
#define CONFIG_INFINIBAND_ON_DEMAND_PAGING 1
#undef CONFIG_INFINIBAND_WQE_FORMAT
#undef CONFIG_INFINIBAND_PA_MR
#undef CONFIG_MLNX_BLOCK_REQUEST_MODULE
#endif

