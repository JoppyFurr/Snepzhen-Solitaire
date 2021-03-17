/*
 * Snepzhen Solitaire
 *
 * A Shenzhen I/O Solitaire clone for the Sega Master System
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "SMSlib.h"

#include "patterns.c"


/* Palette */
const uint8_t palette [16] = {
    0x04,   /* 0 - (table) Dark green */
    0x19,   /* 1 - (table) Light green */
    0x00,   /* 2 - (card) Black */
    0x3f,   /* 3 - (card) White */
    0x02,   /* 3 - (card) Red */
    0x09,   /* 3 - (card) Green */
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

    uint16_t black_six_card [] = {
        158, 11, 11,  12,
         14, 15, 15,  16,
         14, 80, 81,  16,
         14, 82, 83,  16,
         14, 15, 15,  16,
         17, 18, 18, 158 | TILE_FLIPPED_X | TILE_FLIPPED_Y
    };
    uint16_t red_seven_card [] = {
        166, 11, 11,  12,
         14, 15, 15,  16,
         14, 96, 97,  16,
         14, 98, 99,  16,
         14, 15, 15,  16,
         17, 18, 18, 166 | TILE_FLIPPED_X | TILE_FLIPPED_Y
    };
    uint16_t green_eight_card [] = {
        174,  11,  11,  12,
         14,  15,  15,  16,
         14, 112, 113,  16,
         14, 114, 115,  16,
         14,  15,  15,  16,
         17,  18,  18, 174 | TILE_FLIPPED_X | TILE_FLIPPED_Y
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

    SMS_loadTileMapArea (4,  9, &black_six_card, 4, 6);
    SMS_loadTileMapArea (8,  9, &red_seven_card, 4, 6);
    SMS_loadTileMapArea (12,  9, &green_eight_card, 4, 6);
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
