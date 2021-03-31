/*
 * SPI.c
 *
 *  Created on: 27 mars 2021
 *      Author: Audrey Tuffier & Alexis Adde
 */


#include <msp430.h>

/* type def */
typedef unsigned char UCHAR;

UCHAR SPIS_Rx(void) /* SPIS_Rx */
  {
  while( !(USICTL1 & USIIFG) )   /* waiting char by USI counter flag*/
      {
      }
    UCHAR c = USISRL;
    USICNT &= ~USI16B;  /* re-load counter & ignore USISRH*/
    USICNT = 0x08;      /* 8 bits count, that re-enable USI for next transfert */
    return c;
  }


