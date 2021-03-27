#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *sram_magic = "SNEP";


/*
 * Enable SRAM.
 */
void sram_enable (void)
{
    /* Assumes Sega Mapper behaviour */
    uint8_t *reg = (void *) 0xfffc;

    *reg = 0x08;
}


/*
 * Read SRAM data and use if valid.
 */
void sram_read (void)
{
    uint8_t *sram = 0x8000;

    if (memcmp (sram_magic, sram, 4) == 0)
    {
        /* Offset 0x04: RNG */
        srand (*(uint16_t *)(sram + 4));
    }
}


/*
 * Write saved settings into SRAM.
 */
void sram_write (void)
{
    uint8_t *sram = 0x8000;

    /* Offset 0x04: RNG */
    memcpy (sram, sram_magic, 4);
    (* (uint16_t *)(sram + 4)) = rand ();
}
