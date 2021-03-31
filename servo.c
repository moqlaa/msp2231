/*
 *
 * servo.c
 *
 *  Created on: 23 mars 2021
 *  Author: Audrey Tuffier & Alexis Adde
 *
 */

#include <msp430.h>

#define PWM_FREQUENCY   20000 /* Pwm Period */

typedef signed int Sint_32;

void servo_PWM(void)
{
    Sint_32 position = 1500; /* tourne vers la droite */
    Sint_32 inc = 300;

    BCSCTL1 = CALBC1_1MHZ;              /* Clock frequency 1MHz */
    DCOCTL  = CALDCO_1MHZ;              /* Clock frequency 1MHz */

    TACTL   = (TASSEL_2 | MC_1 | ID_0); /* SMCLK, comptage Up, prédividion de 1 */
    TACCTL1 = OUTMOD_7; /* génération signal mod 7 sur P1.2 */
    TACCR0  = PWM_FREQUENCY; /* Fréquence du signal PWM */
    TACCR1  = position; /* Rapport cyclique (position) */

    P1SEL |= BIT2;
    P1DIR |= BIT2;

    while(1)
    {
        TACCR1 = position;
        (void)__delay_cycles(1000000);

        position = position + inc;

        if((position <= 900) || (position >= 2100))
        {
            inc= inc-1;
        }
    }
}

/*
*
*
* arret servo 
*
*
*/
void servo_stop(void) /*Ne fonctionne pas*/
{
    P1DIR &= ~BIT2; /* sur le bit 2 */
}

