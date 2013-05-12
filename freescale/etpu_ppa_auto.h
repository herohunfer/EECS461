

/****************************************************************
 * WARNING this file is automatically generated DO NOT EDIT IT! *
 *                                                              *
 * FILE NAME: etpu_ppa_auto.h      COPYRIGHT (c) Freescale 2004 *
 *                                      All Rights Reserved     *
 * This file generated by:                                      *
 * $RCSfile: etpuc_ppa.c,v $ $Revision: 1.4 $
 *                                                              *
 * This file provides an interface between eTPU code and CPU    *
 * code. All references to the PPA function should be made with *
 * information in this file. This allows only symbolic          *
 * information to be referenced which allows the eTPU code to be*
 * optimized without effecting the CPU code.                    *
 ****************************************************************/
#ifndef _ETPU_PPA_AUTO_H_
#define _ETPU_PPA_AUTO_H_

/* Function Configuration Information */
#define FS_ETPU_PPA_FUNCTION_NUMBER  0 
#define FS_ETPU_PPA_TABLE_SELECT 1 
#define FS_ETPU_PPA_NUM_PARMS 0x0018 

/* Host Service Request Definitions -timer options*/
#define FS_ETPU_PPA_INIT_TCR1 7  
#define FS_ETPU_PPA_INIT_TCR2 5  

/* Function Mode Bit Definitions - pulse/period measurement options - mode options*/
#define FS_ETPU_PPA_LOW_PULSE 0  
#define FS_ETPU_PPA_HIGH_PULSE 2  
#define FS_ETPU_PPA_FALLING_EDGE 1  
#define FS_ETPU_PPA_RISING_EDGE 3  

/* Parameter Definitions */
#define FS_ETPU_PPA_ACCUM_OFFSET  0x0001
#define FS_ETPU_PPA_SAMPLE_TIME_OFFSET  0x0005
#define FS_ETPU_PPA_PERIOD_COUNT_OFFSET  0x000D
#define FS_ETPU_PPA_MAX_COUNT_OFFSET  0x0011
#define FS_ETPU_PPA_RESULT_OFFSET  0x0015
#define FS_ETPU_PPA_STAT_ACC_OFFSET  0x0000
#define FS_ETPU_PPA_STATUS_OFFSET  0x0014

#endif /* _ETPU_PPA_AUTO_H_ */
