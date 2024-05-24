#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "SMSlib.h"
#include "snepzhen.h"

extern settings_t settings;

/* Identification value, change when the format changes */
char *sram_magic = "SNEP_001";


/*
 * Read SRAM data and use if valid.
 */
void sram_load (void)
{
    SMS_enableSRAM ();

    /* Offset 0x00: "SNEP" */
    if (memcmp (sram_magic, &SMS_SRAM [0x00], 8) == 0)
    {
        /* Offset 0x08: RNG state */
        srand (*(uint16_t *)(&SMS_SRAM [0x08]));

        /* Offset 0x0c: Cursor theme */
        settings.cursor_theme = SMS_SRAM [0x0c];

        /* Offset 0x10: Table theme */
        settings.table_theme = SMS_SRAM [0x10];
    }

    SMS_disableSRAM ();
}


/*
 * Write saved settings into SRAM.
 */
void sram_save (void)
{
    SMS_enableSRAM ();

    /* Offset 0x00: "SNEP_nnn" */
    memcpy (&SMS_SRAM [0x00], sram_magic, 8);

    /* Offset 0x08: RNG state */
    (* (uint16_t *)(&SMS_SRAM [0x08])) = rand ();

    /* Offset 0x0c: Cursor theme */
    SMS_SRAM [0x0c] = settings.cursor_theme;

    /* Offset 0x10: Table theme */
    SMS_SRAM [0x10] = settings.table_theme;

    SMS_disableSRAM ();
}
