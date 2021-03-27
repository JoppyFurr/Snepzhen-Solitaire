#include <stdint.h>
#include <stdlib.h>

#include "sram.h"

static uint8_t r_value = 0;

/*
 * Update the rand () seed with data from the R register.
 */
void rng_seed (void)
{
    __asm
        push    af
        ld      a,          r
        ld      (_r_value), a
        pop     af
    __endasm;

    srand (rand () ^ r_value);
    sram_write ();
}
