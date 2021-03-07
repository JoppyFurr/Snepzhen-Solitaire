/*
 * Snepzhen Solitaire
 *
 * A Shenzhen I/O Solitaire clone for the Sega Master System
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "SMSlib.h"

/* Load palette */
uint8_t bg_palette [16] = {
    0x04 /* 0 - Dark green */
};

void main (void)
{
    SMS_loadBGPalette (bg_palette);
    SMS_setBackdropColor (0);

    SMS_displayOn ();

    /* Main loop */
    while (true)
    {
        SMS_waitForVBlank ();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
