/*===========================================================================
#
# EECS461 at the University of Michigan
# System configuration and startup library
#
# Created November 24, 2003 by David Thorsley for MPC555
#
# Revision History:
#   7-25-05 ericjw  for MPC5553
#   8-9-06  lovelljc
#   8-28-06 ericjw
#   1-9-13 jmapatel
#
===========================================================================*/

#include <eecs461.h>


/* should be called as first function in main */
void init_EECS461()
{
	/* set clock to 120MHz */
	init_speed(120);

    /* enable external interrupts */
    asm("wrteei 1");

    /* Set (to 0) the enable pin for the interface board */
    SIU.PCR[205].B.PA = 0b00;
    SIU.PCR[205].B.OBE = 1;   /* enable output buffer */
    SIU.GPDO[205].R = 0;      /* write bit */
}


/* returns (in Hz) the current clock frequency */
uint32_t get_sys_freq(void)
{
    return 8000000 * (FMPLL.SYNCR.B.MFD + 4) / ((FMPLL.SYNCR.B.PREDIV + 1) * ((2 << FMPLL.SYNCR.B.RFD)/2));
}


/* set the clock speed in units of 8 MHz, min 32, max 128 */
void init_speed(long mhz)
{
    /* fsys = fref*(mfd+4)/((prediv+1)*2^rfd) */
    /* fsys = (8 * mfd + 32) MHz */

    /* must have lock (check just in case) */
    while (!FMPLL.SYNSR.B.LOCK)
      ;
    FMPLL.SYNCR.B.LOLRE = 0;
    FMPLL.SYNCR.B.PREDIV = 0;
    FMPLL.SYNCR.B.RFD = 0;
    FMPLL.SYNCR.B.MFD = (mhz-32)/8;
    /* wait for lock again */
    while (!FMPLL.SYNSR.B.LOCK)
      ;
    FMPLL.SYNCR.B.LOLRE = 1;
}


/* initialize floating point unit */
void init_fp()
{
    asm("    mfmsr r3        ");
    asm("    ori r3,r3,0x2000");
    asm("    mtmsr r3        ");
    asm("    isync           ");
}

/* EOF */
