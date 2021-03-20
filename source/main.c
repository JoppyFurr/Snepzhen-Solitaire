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
    0x02,   /* 4 - (card) Red */
    0x09,   /* 5 - (card) Green */
    0x2a,   /* 6 - (card) Light grey */
    0x15,   /* 7 - (card) Dark grey */
};


/*
 * Render one card.
 *
 * Card bits:
 *   [6:7] Zero
 *   [4:5] Card type (0:black, 1:red, 2:green, 3:special)
 *   [0:3] Card value (0-8)
 */
void render_card (uint8_t col, uint8_t y, uint8_t card, bool bottom)
{
    uint16_t card_tiles [] = {
         9, 11, 11, 12,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        14, 15, 15, 16,
        17, 18, 18, 19
    };

    uint8_t value  = card & 0x0f;
    uint8_t tile;

    if ((card & 0x30) == 0x30)
    {
        if (value == 3)
        {
            /* Snep card */
            card_tiles [0]  = CORNER_SNEP;
            card_tiles [23] = CORNER_SNEP | TILE_FLIPPED_X | TILE_FLIPPED_Y;

            for (uint8_t i = 0; i < 16; i++)
            {
                card_tiles [i + 4] = ARTWORK_SNEP + i;
            }
        }
        else
        {
            /* Print card */
            card_tiles [0]  = CORNER_PRINTS + (value * 3);
            card_tiles [1]  = CORNER_PRINTS + (value * 3) + 2;
            card_tiles [22] = CORNER_PRINTS + (value * 3) + 2 | TILE_FLIPPED_X | TILE_FLIPPED_Y;
            card_tiles [23] = CORNER_PRINTS + (value * 3) | TILE_FLIPPED_X | TILE_FLIPPED_Y;

            /* TODO: Print artwork */
        }

        switch (value)
        {
            case 0: /* Claw */
                break;
            case 1: /* Paw */
                break;
            case 2: /* Hoof */
                break;
            case 3: /* Snep */
            default:
                break;
        }
    }
    else
    {
        /* Standard card */
        uint8_t colour = card >> 4;

        /* Card corners */
        tile = CORNER_NUMBERS + value * 6 + colour * 2;
        card_tiles [ 0] = tile;
        card_tiles [23] = tile | TILE_FLIPPED_X | TILE_FLIPPED_Y;

        /* Chinese numbers */
        tile = ARTWORK_CHINESE + value * 12 + colour * 4;
        card_tiles [ 9] = tile;
        card_tiles [10] = tile + 1;
        card_tiles [13] = tile + 2;
        card_tiles [14] = tile + 3;
    }

    if (!bottom)
    {
        /* Show top of card below */
        card_tiles [0] += 1;
        card_tiles [3] = 13;
    }

    SMS_loadTileMapArea (4 * col, y, &card_tiles, 4, 6);
}

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

    render_card (0,  9, 0,        true);
    render_card (1,  9, 1 + 0x10, true);
    render_card (2,  9, 2 + 0x20, true);
    render_card (3,  9, 3,        true);
    render_card (4,  9, 4 + 0x10, true);
    render_card (5,  9, 5 + 0x20, true);
    render_card (6,  9, 6,        true);
    render_card (7,  9, 7 + 0x10, true);
    render_card (0, 10, 8 + 0x20, false);
    render_card (1, 10, 0 + 0x30, false);
    render_card (2, 10, 1 + 0x30, false);
    render_card (3, 10, 2 + 0x30, false);
    render_card (4, 10, 3 + 0x30, false);
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
