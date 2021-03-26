/*
 * Snepzhen Solitaire
 *
 * A Shenzhen I/O Solitaire clone for the Sega Master System
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "SMSlib.h"

#include "rng.h"
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

bool sprite_update = false;

/* Card bits:
 *   [6:7] Zero
 *   [4:5] Card type (0:black, 1:red, 2:green, 3:special)
 *   [0:3] Card value:
 *         0-8: Numbers 1-9
 *         0-2: Claw, paw, hoof prints
 *         3  : Snep
 *  0xff: End of stack.
 */
uint8_t deck [] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x32,
    0x32, 0x32, 0x32, 0x33
};

uint8_t column [8] [14] = {
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff }
};

/* Cursor */
enum cursor_stack_e
{
    CURSOR_COLUMN_1 = 0,
    CURSOR_COLUMN_2,
    CURSOR_COLUMN_3,
    CURSOR_COLUMN_4,
    CURSOR_COLUMN_5,
    CURSOR_COLUMN_6,
    CURSOR_COLUMN_7,
    CURSOR_COLUMN_8,
    CURSOR_DRAGON_SLOT_1,
    CURSOR_DRAGON_SLOT_2,
    CURSOR_DRAGON_SLOT_3,
    CURSOR_DRAGON_BUTTONS,
    CURSOR_FOUNDATION_SNEP,
    CURSOR_FOUNDATION_1,
    CURSOR_FOUNDATION_2,
    CURSOR_FOUNDATION_3,
    CURSOR_STACK_MAX
};

#define CURSOR_DEPTH_MAX 15
uint8_t cursor_stack = CURSOR_COLUMN_1;
uint8_t cursor_depth = CURSOR_DEPTH_MAX;
uint8_t cursor_id [4] = { 0 };


/*
 * Render cursor as sprites.
 */
void move_cursor (uint8_t direction)
{
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t stack_max_depth = 0;

    sprite_update = true;

    /* First, perform the motion */
    switch (direction)
    {
        case PORT_A_KEY_LEFT:
            cursor_stack = (cursor_stack + (CURSOR_STACK_MAX - 1)) % CURSOR_STACK_MAX;
            cursor_depth = CURSOR_DEPTH_MAX;
            break;
        case PORT_A_KEY_RIGHT:
            cursor_stack = (cursor_stack + 1) % CURSOR_STACK_MAX;
            cursor_depth = CURSOR_DEPTH_MAX;
            break;
        case PORT_A_KEY_UP:
            if (cursor_depth > 0)
            {
                cursor_depth--;
            }
            break;
        case PORT_A_KEY_DOWN:
            cursor_depth++;
            break;
    }

    /* Next, calculate the maximum depth for the column */
    if (cursor_stack <= CURSOR_COLUMN_8 && column [cursor_stack] [0] != 0xff)
    {
        for (stack_max_depth == 0; stack_max_depth < CURSOR_DEPTH_MAX; stack_max_depth++)
        {
            if (column [cursor_stack] [stack_max_depth + 1] == 0xff)
            {
                break;
            }
        }
    }

    /* Enforce the limit */
    if (cursor_depth > stack_max_depth)
    {
        cursor_depth = stack_max_depth;
    }

    /* Cursor coordinates */
    cursor_x = (cursor_stack & 0x07) * 32 + 16;
    if (cursor_stack > CURSOR_COLUMN_8)
    {
        cursor_y = 12;
    }
    else
    {
        cursor_y = cursor_depth * 8 + 76;
    }

    SMS_updateSpritePosition (cursor_id [0], cursor_x,     cursor_y);
    SMS_updateSpritePosition (cursor_id [1], cursor_x + 8, cursor_y);
    SMS_updateSpritePosition (cursor_id [2], cursor_x,     cursor_y + 8);
    SMS_updateSpritePosition (cursor_id [3], cursor_x + 8, cursor_y + 8);
}


/*
 * Deal a new game.
 */
void deal (void)
{
    uint8_t i;

    rng_seed ();

    /* Shuffle the deck */
    for (i = 39; i >= 1; i--)
    {
        uint8_t temp = deck [i];
        uint8_t swap_i = rand () % (i + 1);

        deck [i] = deck [swap_i];
        deck [swap_i] = temp;
    }

    /* Place the cards */
    i = 0;
    for (uint8_t col = 0; col < 8; col++)
    {
        for (uint8_t depth = 0; depth < 5; depth++)
        {
            column [col] [depth] = deck [i++];
        }

        column [col] [5] = 0xff;
    }

    cursor_stack = CURSOR_COLUMN_1;
    cursor_depth = CURSOR_DEPTH_MAX;
    move_cursor (PORT_A_KEY_DOWN);
}


/*
 * Render one card.
 */
void render_card (uint8_t col, uint8_t y, uint8_t card, bool stacked, bool covered)
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

            tile = ARTWORK_PRINTS + value * 4;
            card_tiles [ 9] = tile;
            card_tiles [10] = tile + 1;
            card_tiles [13] = tile + 2;
            card_tiles [14] = tile + 3;
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

    if (stacked)
    {
        /* Show top of card below */
        card_tiles [0] += 1;
        card_tiles [3] = 13;
    }

    SMS_loadTileMapArea (4 * col, y, &card_tiles, 4, covered ? 1 : 6);
}

/*
 * Renders the cards.
 */
void render_tiles (void)
{
    uint16_t blank_line [] = {
        0, 0, 0, 0
    };
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
    for (int col = 0; col < 8; col++)
    {
        if (column [col] [0] == 0xff)
        {
            SMS_loadTileMapArea (4 * col, 9, &empty_slot, 4, 6);
        }
        else
        {
            uint8_t depth;
            for (depth = 0; depth < 13; depth++)
            {
                uint8_t card = column [col] [depth];
                uint8_t next = column [col] [depth + 1];

                if (card == 0xff)
                {
                    break;
                }

                render_card (col, 9 + depth, card, depth, next != 0xff);
            }

            /* Clear area below stack */
            depth += 5;
            while (depth < 18)
            {
                SMS_loadTileMapArea (4 * col, 9 + depth, &blank_line, 4, 1);
                depth++;
            }
        }
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

    SMS_useFirstHalfTilesforSprites (true);
    SMS_initSprites ();
    cursor_id [0] = SMS_addSprite (0, 0, (uint8_t) (CURSOR_WHITE    ));
    cursor_id [1] = SMS_addSprite (0, 0, (uint8_t) (CURSOR_WHITE + 1));
    cursor_id [2] = SMS_addSprite (0, 0, (uint8_t) (CURSOR_WHITE + 2));
    cursor_id [3] = SMS_addSprite (0, 0, (uint8_t) (CURSOR_WHITE + 3));
    move_cursor (PORT_A_KEY_DOWN);
    SMS_copySpritestoSAT ();

    SMS_displayOn ();

    deal ();
    render_tiles ();

    /* Main loop */
    while (true)
    {
        static uint16_t keys_previous = 0;
        uint16_t keys = SMS_getKeysStatus ();

        /* Logic */
        move_cursor (keys & ~keys_previous);
        keys_previous = keys;

        /* Render */
        SMS_waitForVBlank ();

        if (sprite_update)
        {
            SMS_copySpritestoSAT ();
            sprite_update = false;
        }
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
