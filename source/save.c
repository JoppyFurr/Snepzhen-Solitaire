#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "SMSlib.h"

char *sram_magic = "SNEP";


/*
 * Read SRAM data and use if valid.
 */
void sram_load (void)
{
    SMS_enableSRAM ();

    /* Offset 0x00: "SNEP" */
    if (memcmp (sram_magic, &SMS_SRAM [0], 4) == 0)
    {
        /* Offset 0x04: RNG state */
        srand (*(uint16_t *)(&SMS_SRAM [4]));
    }

    SMS_disableSRAM ();
}


/*
 * Write saved settings into SRAM.
 */
void sram_save (void)
{
    SMS_enableSRAM ();

    /* Offset 0x00: "SNEP" */
    memcpy (&SMS_SRAM [0], sram_magic, 4);

    /* Offset 0x04: RNG state */
    (* (uint16_t *)(&SMS_SRAM [4])) = rand ();

    SMS_disableSRAM ();
}
