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
    0x00,   /* 2 - Black */
    0x3f,   /* 3 - White */
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

    /* 09 - Card top-left */
    0x00000700, 0x00000f07, 0x00001f0f, 0x00003f1f,
    0x00003f1f, 0x00003f1f, 0x00003f1f, 0x00003f1f,
    /* 10 - Card top-left stacked */
    0x00003f18, 0x00003f17, 0x00003f0f, 0x00003f1f,
    0x00003f1f, 0x00003f1f, 0x00003f1f, 0x00003f1f,
    /* 11 - Card top-edge */
    0x0000ff00, 0x0000ffff, 0x0000ffff, 0x0000ffff,
    0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff,
    /* 12 - Card top-right */
    0x0000e000, 0x0000f0e0, 0x0000f8f0, 0x0000fcf8,
    0x0000fcf8, 0x0000fcf8, 0x0000fcf8, 0x0000fcf8,
    /* 13 - Card top-right stacked */
    0x0000fc18, 0x0000fce8, 0x0000fcf0, 0x0000fcf8,
    0x0000fcf8, 0x0000fcf8, 0x0000fcf8, 0x0000fcf8,
    /* 14 - Card left-edge */
    0x00003f1f, 0x00003f1f, 0x00003f1f, 0x00003f1f,
    0x00003f1f, 0x00003f1f, 0x00003f1f, 0x00003f1f,
    /* 15 - Card blank-middle */
    0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff,
    0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff,
    /* 16 - Card right-edge */
    0x0000fcf8, 0x0000fcf8, 0x0000fcf8, 0x0000fcf8,
    0x0000fcf8, 0x0000fcf8, 0x0000fcf8, 0x0000fcf8,
    /* 17 - Card bottom-left */
    0x00003f1f, 0x00003f1f, 0x00003f1f, 0x00003f1f,
    0x00003f1f, 0x00001f0f, 0x00000f07, 0x00000700,
    /* 18 - Card bottom-edge */
    0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ffff,
    0x0000ffff, 0x0000ffff, 0x0000ffff, 0x0000ff00,
    /* 19 - Card bottom-right */
    0x0000fcf8, 0x0000fcf8, 0x0000fcf8, 0x0000fcf8,
    0x0000fcf8, 0x0000f8f0, 0x0000f0e0, 0x0000e000,
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


    uint16_t blank_card [] = {
         9, 11, 11, 12,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        17, 18, 18, 19
    };

    uint16_t blank_card_stacked [] = {
        10, 11, 11, 13,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        17, 18, 18, 19
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

    SMS_loadTileMapArea (0,  9, &blank_card, 4, 6);
    SMS_loadTileMapArea (0, 10, &blank_card_stacked, 4, 6);
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
