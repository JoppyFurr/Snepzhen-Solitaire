/*
 * Snepzhen Solitaire
 *
 * A Shenzhen I/O Solitaire clone for the Sega Master System
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "SMSlib.h"


/* Palette */
const uint8_t palette [16] = {
    0x04,   /* 0 - Dark green */
    0x19,   /* 1 - Light green */
};

/* Patterns */
const uint32_t patterns [] = {
    /* 00 - Blank */
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    /* 01 - Outline top-left */
    0x00000007, 0x00000008, 0x00000010, 0x00000020,
    0x00000020, 0x00000020, 0x00000020, 0x00000020,
    /* 02 - Outline top-edge */
    0x000000ff, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    /* 03 - Outline top-right */
    0x000000e0, 0x00000010, 0x00000008, 0x00000004,
    0x00000004, 0x00000004, 0x00000004, 0x00000004,
    /* 04 - Outline left-edge */
    0x00000020, 0x00000020, 0x00000020, 0x00000020,
    0x00000020, 0x00000020, 0x00000020, 0x00000020,
    /* 05 - Outline right-edge */
    0x00000004, 0x00000004, 0x00000004, 0x00000004,
    0x00000004, 0x00000004, 0x00000004, 0x00000004,
    /* 06 - Outline bottom-left */
    0x00000020, 0x00000020, 0x00000020, 0x00000020,
    0x00000020, 0x00000010, 0x00000008, 0x00000007,
    /* 07 - Outline bottom-edge */
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000ff,
    /* 08 - Outline bottom-right */
    0x00000004, 0x00000004, 0x00000004, 0x00000004,
    0x00000004, 0x00000008, 0x00000010, 0x000000e0,
};


/*
 * Renders the cards.
 */
void render_tiles (void)
{
    uint16_t empty_slot [] = {
        1, 2, 2, 3,
        4, 0, 0, 5,
        4, 0, 0, 5,
        4, 0, 0, 5,
        4, 0, 0, 5,
        6, 7, 7, 8
    };

    /* Dragons, foundations. */
    for (int i = 0; i < 8; i++)
    {
        if (i == 3)
        {
            /* A gap after the third slot */
            continue;
        }
        SMS_loadTileMapArea (4 * i, 1, &empty_slot, 4, 6);
    }

    /* Tableau columns */
    for (int i = 0; i < 8; i++)
    {
        SMS_loadTileMapArea (4 * i, 9, &empty_slot, 4, 6);
    }
}


/*
 * Entry point.
 */
void main (void)
{
    /* Setup */
    SMS_loadBGPalette (palette);
    SMS_loadSpritePalette (palette);
    SMS_setBackdropColor (0);
    SMS_loadTiles (patterns, 0, sizeof (patterns));
    SMS_displayOn ();

    render_tiles ();

    /* Main loop */
    while (true)
    {
        SMS_waitForVBlank ();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
