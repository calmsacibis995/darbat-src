# Location of TCRs within UTCB.
# Note: Keep up to date with vregs.h

#define __L4_TCR_USER_NUM			(10)
#define __L4_TCR_USER_OFFSET			(54)
#define __L4_TCR_PLATFORM_NUM			(6)
#define __L4_TCR_PLAT_TLS			(48)	# Thread local storage
#define __L4_TCR_PLATFORM_OFFSET		(48)

#define __L4_TCR_MR_OFFSET		        (16)

#define __L4_TCR_KERNEL_RESERVED1		(15)
#define __L4_TCR_KERNEL_RESERVED0		(14)

#define __L4_TCR_PREEMPTED_IP			(13)
#define __L4_TCR_PREEMPT_CALLBACK_IP		(12)
#define __L4_TCR_VIRTUAL_ACTUAL_SENDER		(11)
#define __L4_TCR_INTENDED_RECEIVER		(10)
#define __L4_TCR_ERROR_CODE			(9)
#define __L4_TCR_PROCESSOR_NO			(8)
#define __L4_TCR_NOTIFY_BITS			(7)
#define __L4_TCR_NOTIFY_MASK			(6)
#define __L4_TCR_ACCEPTOR			(5)
#define __L4_TCR_COP_FLAGS			(4)
#define __L4_TCR_PREEMPT_FLAGS			(4)
#define __L4_TCR_EXCEPTION_HANDLER		(3)
#define __L4_TCR_PAGER				(2)
#define __L4_TCR_USER_DEFINED_HANDLE		(1)
#define __L4_TCR_MY_GLOBAL_ID			(0)
