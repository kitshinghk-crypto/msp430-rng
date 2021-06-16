#include <msp430.h>
#include "rand.h"


unsigned int rand(void)
{
    int i, j;
    unsigned int result = 0;

    for (i = 0; i < 16; i++)
    {
        unsigned int ones = 0;
        for (j = 0; j < 5; j++)
        {
            startTimer();
            while (!(CCIFG & TA1CCTL0))
                ;
            stopTimer();
            TA0CTL &= MC_0;
            TA1CTL &= MC_0;
            TA1CCTL0 &= ~CCIFG;
            if (1 & TA0R)
                ones++;
            TA0R = 0;
        }
        result >>= 1;
        if (ones >= 3)
            result |= 0x8000;
    }
    return result;

}


static void startTimer()
{
    TA0CCTL0 = CAP | CM_1 | CCIS_1;
    TA0CTL = TASSEL_2 | MC_2;
    TA1CCR0 = 1;
    TA1CCTL0 = CCIE | OUTMOD_3;
    TA1CTL = TASSEL_1 | MC_1;
}

static void stopTimer()
{
    TA0CTL &= MC_0;
    TA1CTL &= MC_0;
}

