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
#define TYPE_BITS   0x30
#define VALUE_BITS  0x0f

uint8_t deck [] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x31, 0x31, 0x32,
    0x32, 0x32, 0x32, 0x33
};

uint8_t stack [15] [16] = {
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }
};

uint8_t held [16] = { 0xff };
uint8_t came_from = 0xff;

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


/*
 * Calculate the index of the top card in the selected stack.
 */
uint8_t top_card (uint8_t s)
{
    uint8_t depth;

    for (depth = 0; depth < CURSOR_DEPTH_MAX; depth++)
    {
        if (stack [s] [depth + 1] == 0xff)
        {
            break;
        }
    }

    return depth;
}


/*
 * Render the cursor and its held cards, as sprites.
 */
void cursor_render (void)
{
    uint8_t cursor_x;
    uint8_t cursor_y;

    /* Clear any previous sprites */
    SMS_initSprites ();

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

    SMS_addSprite (cursor_x,     cursor_y,     (uint8_t) (CURSOR_WHITE    ));
    SMS_addSprite (cursor_x + 8, cursor_y,     (uint8_t) (CURSOR_WHITE + 1));
    SMS_addSprite (cursor_x,     cursor_y + 8, (uint8_t) (CURSOR_WHITE + 2));
    SMS_addSprite (cursor_x + 8, cursor_y + 8, (uint8_t) (CURSOR_WHITE + 3));

    sprite_update = true;
}


/*
 * Calculate the new cursor position after d-pad input.
 */
void cursor_move (uint8_t direction)
{
    uint8_t stack_max_depth = 0;
    uint8_t stack_idx;

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
            if (cursor_stack <= CURSOR_COLUMN_8 &&
                held [0] == 0xff && cursor_depth > 0)
            {
                cursor_depth--;
            }
            break;
        case PORT_A_KEY_DOWN:
            cursor_depth++;
            break;
    }

    /* Next, calculate the maximum depth for the column */
    stack_idx = (cursor_stack < CURSOR_DRAGON_BUTTONS) ? cursor_stack : cursor_stack - 1;
    if (stack [stack_idx] [0] != 0xff)
    {
        stack_max_depth = top_card (stack_idx);
    }

    /* Enforce the limit */
    if (cursor_depth > stack_max_depth)
    {
        cursor_depth = stack_max_depth;
    }

    cursor_render ();
}


/*
 * Pick up the selected card.
 * TODO: Only allow picking from a dragon slot when it contains exactly one card.
 */
void cursor_pick (void)
{
    uint8_t i;
    uint8_t stack_idx = (cursor_stack < CURSOR_DRAGON_BUTTONS) ? cursor_stack : cursor_stack - 1;

    /* Check if the selected cards can be picked up together */
    if (stack [stack_idx] [cursor_depth + 1] != 0xff)
    {
        uint8_t previous_card = 0;
        for (i = 0; stack [stack_idx] [cursor_depth + i] != 0xff; i++)
        {
            uint8_t card = stack [stack_idx] [cursor_depth + i];

            /* Special cards cannot be stacked */
            if ((card & TYPE_BITS) == 0x30)
            {
                return;
            }

            if (i > 0)
            {
                if (cursor_stack <= CURSOR_COLUMN_8)
                {
                    /* Colours must alternate */
                    if ((card & TYPE_BITS) == (previous_card & TYPE_BITS))
                    {
                        return;
                    }

                    /* Value must decrease */
                    if ((card & VALUE_BITS) != (previous_card & VALUE_BITS) - 1)
                    {
                        return;
                    }
                }
            }

            previous_card = card;
        }
    }

    /* Move the selected stack into the hand */
    for (i = 0; stack [stack_idx] [cursor_depth + i] != 0xff; i++)
    {
        held [i] = stack [stack_idx] [cursor_depth + i];
        stack [stack_idx] [cursor_depth + i] = 0xff;
    }
    held [i] = 0xff;

    came_from = cursor_stack;

    /* Point at the new top card in the stack */
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (PORT_A_KEY_DOWN);
}


/*
 * Place the selected card.
 */
void cursor_place (void)
{
    uint8_t i;
    uint8_t stack_idx = (cursor_stack < CURSOR_DRAGON_BUTTONS) ? cursor_stack : cursor_stack - 1;

    /* Check if cards are allowed to move here */
    if (cursor_stack != came_from)
    {
        uint8_t stack_card = stack [stack_idx] [cursor_depth];

        if (cursor_stack <= CURSOR_COLUMN_8)
        {
            if (stack_card != 0xff)
            {
                /* Special cards cannot be stacked */
                if (((stack_card & 0x30) == 0x30) ||
                    ((held [0]   & 0x30) == 0x30))
                {
                    return;
                }

                /* Colours must alternate */
                if ((stack_card & 0x30) == (held [0] & 0x30))
                {
                    return;
                }

                /* Value must decrease */
                if ((stack_card & VALUE_BITS) != (held [0] & VALUE_BITS) + 1)
                {
                    return;
                }
            }
        }
        else if (cursor_stack <= CURSOR_DRAGON_SLOT_3)
        {
            /* Only single cards may be placed in the dragon slots */
            if ((stack_card != 0xff) || (held [1] != 0xff))
            {
                return;
            }
        }
        else if (cursor_stack <= CURSOR_DRAGON_BUTTONS)
        {
            /* Not a card slot */
            return;
        }
        else if (cursor_stack <= CURSOR_FOUNDATION_SNEP)
        {
            /* Only the snep card may be placed in the snep card slot */
            if (held [0] != 0x33)
            {
                return;
            }
        }
        else if (cursor_stack <= CURSOR_FOUNDATION_3)
        {
            /* No special cards, and only one card at a time */
            if ((held [0] & TYPE_BITS) == 0x30 || held [1] != 0xff)
            {
                return;
            }

            /* Only a '1' can be placed on an empty slot */
            if (stack [stack_idx] [0] == 0xff)
            {
                if ((held [0] & VALUE_BITS) != 0)
                {
                    return;
                }
            }
            else
            {
                /* Cards in a foundation must all be the same colour */
                if ((stack_card & TYPE_BITS) != (held [0] & TYPE_BITS))
                {
                    return;
                }
                /* Cards in a foundation must be in increasing order */
                if ((stack_card & VALUE_BITS) != (held [0] & VALUE_BITS) - 1)
                {
                    return;
                }
            }
        }
        else
        {
            /* Invalid */
            return;
        }

    }

    /* Place at the first empty slot, not the last full slot */
    if (stack [stack_idx] [0] != 0xff)
    {
        cursor_depth++;
    }

    /* Move the cards from the hand */
    for (i = 0; held [i] != 0xff; i++)
    {
        stack [stack_idx] [cursor_depth + i] = held [i];
        held [i] = 0xff;
    }
    stack [stack_idx] [cursor_depth + i] = 0xff;

    came_from = 0xff;

    /* Point at the new top card in the stack */
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (PORT_A_KEY_DOWN);
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
            stack [col] [depth] = deck [i++];
        }

        stack [col] [5] = 0xff;
    }

    cursor_stack = CURSOR_COLUMN_1;
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (PORT_A_KEY_DOWN);
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

    uint8_t value = card & VALUE_BITS;
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

    /* Dragons & Foundations*/
    for (uint8_t i = 0; i < 7; i++)
    {
        uint8_t col = (i < 3) ? i : i + 1;

        if (stack [i + 8] [0] != 0xff)
        {
            uint8_t depth = top_card (i + 8);
            render_card (col, 1, stack [i + 8] [depth], false, false);
        }
        else
        {
            SMS_loadTileMapArea (4 * col, 1, &empty_slot, 4, 6);
        }
    }

    /* Tableau columns */
    for (int col = 0; col < 8; col++)
    {
        uint8_t depth;
        if (stack [col] [0] == 0xff)
        {
            SMS_loadTileMapArea (4 * col, 9, &empty_slot, 4, 6);
            depth = 1;
        }
        else
        {
            for (depth = 0; depth < 13; depth++)
            {
                uint8_t card = stack [col] [depth];
                uint8_t next = stack [col] [depth + 1];

                if (card == 0xff)
                {
                    break;
                }

                render_card (col, 9 + depth, card, depth, next != 0xff);
            }
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
    SMS_copySpritestoSAT ();

    SMS_displayOn ();

    deal ();
    render_tiles ();

    /* Main loop */
    while (true)
    {
        static uint16_t keys_previous = 0;
        uint16_t keys = SMS_getKeysStatus ();
        uint16_t keys_pressed = (keys & ~keys_previous);

        /* Logic */
        cursor_move (keys_pressed);
        if (keys_pressed & PORT_A_KEY_1)
        {
            if (held [0] == 0xff)
            {
                cursor_pick ();
            }
            else
            {
                cursor_place ();
            }

            /* Update cards in background layer */
            render_tiles ();
        }

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
