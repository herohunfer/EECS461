/**************************************************************************
 * serial.h                                                               *
 * University of Michigan                                                 *
 * EECS 461, Embedded Control Systems, Fall 2003                          *
 * See Chapter 14 in MPC555 User's Manual                                 *
 * Created: 10/19/1999 by Noah J. Cowan                                   *
 * Updated: 9/12/2003  by Ganesh S. Dasika                                *
 * Updated: 11/24/2003 by David Thorsley                                  *
 * Updated: 6/23/2005  by Eric Williams                                   *
 * Updated: 7/10/2006  lovelljc                                           *
 * Updated: 8/28/2006  ericjw                                             *
 **************************************************************************/

#include <serial.h>
#include <mpc5553.h>
#include <eecs461.h>

void init_COM(int port, int baudrate)
{
    unsigned long SYSTEM_FREQUENCY;

    SYSTEM_FREQUENCY = get_sys_freq();

    switch (port)
    {
    case 2:
        /* set up sci_b output pin mapping */
        SIU.PCR[91].B.PA = 0b11;
        SIU.PCR[92].B.PA = 0b11;

        /* set up sci_b (serial) module */
        ESCI_B.CR2.B.MDIS = 0;
        ESCI_B.CR1.B.SBR = SYSTEM_FREQUENCY/16/baudrate;
        ESCI_B.CR1.B.TE = 1;
        ESCI_B.CR1.B.RE = 1;

        break;

    case 1:
    default:
        /* set up sci_a output pin mapping */
        SIU.PCR[89].B.PA = 0b11;
        SIU.PCR[90].B.PA = 0b11;

        /* set up sci_a (serial) module */
        ESCI_A.CR2.B.MDIS = 0;
        ESCI_A.CR1.B.SBR = SYSTEM_FREQUENCY/16/baudrate;
        ESCI_A.CR1.B.TE = 1;
        ESCI_A.CR1.B.RE = 1;

    break;
    }
}

char serial_putchar(int port, unsigned char sbyte)
{
    while(!serial_readyToSend(port))
      ;  /* wait for ready to send */

    if (port == 1)
        {
        ESCI_A.SR.R = 0x80000000;
        ESCI_A.DR.B.D = sbyte;
        }
    else if (port == 2)
        {
        ESCI_B.SR.R = 0x80000000;
        ESCI_B.DR.B.D = sbyte;
        }

    return 0;
}

void serial_puts(int port, char *sptr)
{
    while(*sptr)
    {
        serial_putchar(port, *sptr);
        ++sptr;
    }
}

/* returns 1 if transmit register ready for another byte */
char serial_readyToSend(int port)
{
    unsigned long status;

    do
    {   /* wait for transmit byte sent to the shift register, ready for another */
        if (port == 1)
            status = ESCI_A.SR.B.TDRE;
        else if (port == 2)
            status = ESCI_B.SR.B.TDRE;
    } while(!status);

    return 1;
}


/* returns 1 if data is waiting to be received */
char serial_readyToReceive(int port)
{
    if (port == 1)
        return (char)ESCI_A.SR.B.RDRF;
    else
        return (char)ESCI_B.SR.B.RDRF;
}


/* wait for a byte to be received from the serial port */
char serial_getchar(int port)
{
    while(serial_readyToReceive(port) == 0)
      ; /* wait for new incoming data */

    if (port == 1)
        {
        ESCI_A.SR.R = 0x20000000;                       /* clear data-ready flag */
        return (unsigned char)(ESCI_A.DR.B.D & 0x00ff); /* read the port */
        }
    else
        {
        ESCI_B.SR.R = 0x20000000;                       /* clear data-ready flag */
        return (unsigned char)(ESCI_B.DR.B.D & 0x00ff); /* read the port */
        }
}


/*void InterruptHandler(int port, unsigned long exceptNumber){
    serial_puts(port, "\nException Interrupt");
}*/
