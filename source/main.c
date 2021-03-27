/*
 * Snepzhen Solitaire
 *
 * A Shenzhen I/O Solitaire clone for the Sega Master System
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "SMSlib.h"

#include "sram.h"
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

#define HELD 15

uint8_t stack [16] [16] = {
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff },
    { 0xff }, { 0xff }, { 0xff }, { 0xff }
};
bool stack_changed [16] = { false };
uint8_t came_from = 0xff;

bool button_active [3] = { false };

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
 * Check the any dragon buttons are active.
 */
void check_dragons (void)
{
    bool empty_slot = false;
    bool in_slot [3] = { false };
    uint8_t count [3] = { 0 };

    /* Check for empty slots */
    if (stack [CURSOR_DRAGON_SLOT_1] [0] == 0xff ||
        stack [CURSOR_DRAGON_SLOT_2] [0] == 0xff ||
        stack [CURSOR_DRAGON_SLOT_3] [0] == 0xff)
    {
        empty_slot = true;
    }

    for (uint8_t stack_idx = 0; stack_idx <= CURSOR_DRAGON_SLOT_3; stack_idx++)
    {
        uint8_t card = stack [stack_idx] [top_card (stack_idx)];

        for (uint8_t kind = 0; kind < 3; kind++)
        {
            if (card == (0x30 + kind))
            {
                count [kind]++;

                if (stack_idx >= CURSOR_DRAGON_SLOT_1)
                {
                    in_slot [kind] = true;
                }
            }
        }
    }

    /* Light up the button if all of a kind are visible and have somewhere to go */
    for (uint8_t kind = 0; kind < 3; kind++)
    {
        button_active [kind] = (count [kind] == 4) && (empty_slot || in_slot [kind]);
    }
}


/*
 * Stack four dragon cards into a slot.
 */
void stack_dragons (void)
{
    uint8_t dragon_idx = cursor_depth;
    uint8_t card_match = 0x30 + dragon_idx;
    uint8_t dest_idx = 0xff;

    /* First, see if we already have a slot */
    for (uint8_t stack_idx = CURSOR_DRAGON_SLOT_1; stack_idx <= CURSOR_DRAGON_SLOT_3; stack_idx++)
    {
        if (stack [stack_idx] [0] == card_match)
        {
            dest_idx = stack_idx;
            break;
        }
    }

    /* If not, choose the first empty slot */
    if (dest_idx == 0xff)
    {
        for (uint8_t stack_idx = CURSOR_DRAGON_SLOT_1; stack_idx <= CURSOR_DRAGON_SLOT_3; stack_idx++)
        {
            if (stack [stack_idx] [0] == 0xff)
            {
                dest_idx = stack_idx;
                break;
            }
        }
    }

    /* Remove the dragons from wherever they may be */
    for (uint8_t stack_idx = 0; stack_idx <= CURSOR_DRAGON_SLOT_3; stack_idx++)
    {
        uint8_t top = top_card (stack_idx);

        if (stack [stack_idx] [top] == card_match)
        {
            stack [stack_idx] [top] = 0xff;
            stack_changed [stack_idx] = true;
        }
    }

    /* Place all four dragons into the destination slot */
    for (uint8_t i = 0; i < 4; i++)
    {
        stack [dest_idx] [i] = card_match;
    }
    stack [dest_idx] [4] = 0xff;
    stack_changed [dest_idx] = true;
}


/*
 * Render a single card to an array of tile indexes.
 */
void render_card_tiles (uint16_t *buf, uint8_t card, bool stacked)
{
    uint8_t value = card & VALUE_BITS;
    uint8_t tile;

    uint16_t card_tiles [] = {
        BLANK_CARD +  0, BLANK_CARD +  2, BLANK_CARD +  2, BLANK_CARD +  3,
        BLANK_CARD +  5, BLANK_CARD +  6, BLANK_CARD +  6, BLANK_CARD +  7,
        BLANK_CARD +  5, BLANK_CARD +  6, BLANK_CARD +  6, BLANK_CARD +  7,
        BLANK_CARD +  5, BLANK_CARD +  6, BLANK_CARD +  6, BLANK_CARD +  7,
        BLANK_CARD +  5, BLANK_CARD +  6, BLANK_CARD +  6, BLANK_CARD +  7,
        BLANK_CARD +  8, BLANK_CARD +  9, BLANK_CARD +  9, BLANK_CARD + 10
    };

    if ((card & TYPE_BITS) == 0x30)
    {
        if (value == 3)
        {
            /* Snep card */
            card_tiles [0]  = CORNER_SNEP;
            card_tiles [23] = CORNER_SNEP + 2;

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

        /* Chinese numbers */
        tile = ARTWORK_NUMBERS + value * 12 + colour * 4;
        card_tiles [ 9] = tile;
        card_tiles [10] = tile + 1;
        card_tiles [13] = tile + 2;
        card_tiles [14] = tile + 3;
    }

    if (stacked)
    {
        /* Show top of card below */
        card_tiles [0] += 1;
        card_tiles [3] += 1;
    }

    memcpy (buf, card_tiles, sizeof (card_tiles));
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

    if (cursor_stack == CURSOR_DRAGON_BUTTONS)
    {
        cursor_y = (cursor_depth * 16) + 16;
    }
    else if (cursor_stack > CURSOR_COLUMN_8)
    {
        cursor_y = 12;
    }
    else
    {
        cursor_y = (cursor_depth * 8) + 76;
    }

    /* Offset the cursor if we're holding a card */
    if (stack [HELD] [0] != 0xff)
    {
        cursor_x += 2;
        cursor_y += 12;
    }

    SMS_addSprite (cursor_x,     cursor_y,     (uint8_t) (CURSOR_WHITE    ));
    SMS_addSprite (cursor_x + 8, cursor_y,     (uint8_t) (CURSOR_WHITE + 1));
    SMS_addSprite (cursor_x,     cursor_y + 8, (uint8_t) (CURSOR_WHITE + 2));
    SMS_addSprite (cursor_x + 8, cursor_y + 8, (uint8_t) (CURSOR_WHITE + 3));

    /* Render held cards as sprites */
    if (stack [HELD] [0] != 0xff)
    {
        uint8_t card_x = cursor_x - 16;
        uint8_t top = top_card (HELD);

        for (uint8_t i = top; i != 0xff; i--)
        {
            uint8_t card_y = cursor_y + (8 * i) - 4;
            uint16_t card_tiles [24];

            render_card_tiles (card_tiles, stack [HELD] [i], i > 0);

            for (uint8_t y = 0; y < 6; y++)
            {
                for (uint8_t x = 0; x < 4; x++)
                {
                    SMS_addSprite (card_x + (8 * x), card_y + (8 * y), (uint8_t) card_tiles [x + (4 * y)]);
                }

                /* Only the top card is fully drawn */
                if (i != top)
                {
                    break;
                }
            }
        }
    }

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

            if (cursor_stack == CURSOR_DRAGON_BUTTONS)
            {
                if (stack [HELD] [0] != 0xff)
                {
                    /* Skip over the buttons if holding a card */
                    cursor_stack--;
                }
                else
                {
                    /* Start on the top button */
                    cursor_depth = 0;
                }
            }
            break;

        case PORT_A_KEY_RIGHT:
            cursor_stack = (cursor_stack + 1) % CURSOR_STACK_MAX;
            cursor_depth = CURSOR_DEPTH_MAX;

            /* Skip over the buttons if holding a card */
            if (cursor_stack == CURSOR_DRAGON_BUTTONS)
            {
                if (stack [HELD] [0] != 0xff)
                {
                    /* Skip over the buttons if holding a card */
                    cursor_stack++;
                }
                else
                {
                    /* Start on the top button */
                    cursor_depth = 0;
                }
            }
            break;

        case PORT_A_KEY_UP:
            if (cursor_depth > 0 &&
                    ((cursor_stack == CURSOR_DRAGON_BUTTONS) ||
                     (cursor_stack <= CURSOR_COLUMN_8 && stack [HELD] [0] == 0xff)))
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
    if (cursor_stack == CURSOR_DRAGON_BUTTONS)
    {
        stack_max_depth = 2;
    }
    else if (stack [stack_idx] [0] != 0xff)
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

    /* Once a stack of dragons is stored, it stays */
    if (cursor_stack >= CURSOR_DRAGON_SLOT_1 && cursor_stack <= CURSOR_DRAGON_SLOT_3)
    {
        if (cursor_depth > 0)
        {
            return;
        }
    }

    /* Move the selected stack into the hand */
    for (i = 0; stack [stack_idx] [cursor_depth + i] != 0xff; i++)
    {
        stack [HELD] [i] = stack [stack_idx] [cursor_depth + i];
        stack [stack_idx] [cursor_depth + i] = 0xff;
    }
    stack [HELD] [i] = 0xff;
    stack_changed [stack_idx] = true;

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
                if (((stack_card       & 0x30) == 0x30) ||
                    ((stack [HELD] [0] & 0x30) == 0x30))
                {
                    return;
                }

                /* Colours must alternate */
                if ((stack_card & 0x30) == (stack [HELD] [0] & 0x30))
                {
                    return;
                }

                /* Value must decrease */
                if ((stack_card & VALUE_BITS) != (stack [HELD] [0] & VALUE_BITS) + 1)
                {
                    return;
                }
            }
        }
        else if (cursor_stack <= CURSOR_DRAGON_SLOT_3)
        {
            /* Only single cards may be placed in the dragon slots */
            if ((stack_card != 0xff) || (stack [HELD] [1] != 0xff))
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
            if (stack [HELD] [0] != 0x33)
            {
                return;
            }
        }
        else if (cursor_stack <= CURSOR_FOUNDATION_3)
        {
            /* No special cards, and only one card at a time */
            if ((stack [HELD] [0] & TYPE_BITS) == 0x30 || stack [HELD] [1] != 0xff)
            {
                return;
            }

            /* Only a '1' can be placed on an empty slot */
            if (stack [stack_idx] [0] == 0xff)
            {
                if ((stack [HELD] [0] & VALUE_BITS) != 0)
                {
                    return;
                }
            }
            else
            {
                /* Cards in a foundation must all be the same colour */
                if ((stack_card & TYPE_BITS) != (stack [HELD] [0] & TYPE_BITS))
                {
                    return;
                }
                /* Cards in a foundation must be in increasing order */
                if ((stack_card & VALUE_BITS) != (stack [HELD] [0] & VALUE_BITS) - 1)
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
    for (i = 0; stack [HELD] [i] != 0xff; i++)
    {
        stack [stack_idx] [cursor_depth + i] = stack [HELD] [i];
        stack [HELD] [i] = 0xff;
    }
    stack [stack_idx] [cursor_depth + i] = 0xff;
    stack_changed [stack_idx] = true;

    came_from = 0xff;

    /* Point at the new top card in the stack */
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (PORT_A_KEY_DOWN);
}


/*
 * Render one card to the background.
 */
void render_card_background (uint8_t col, uint8_t y, uint8_t card, bool stacked, bool covered)
{
    uint16_t card_tiles [24];

    render_card_tiles (card_tiles, card, stacked);

    SMS_loadTileMapArea (4 * col, y, &card_tiles, 4, covered ? 1 : 6);
}

/*
 * Renders the cards.
 */
void render_background (void)
{
    uint16_t blank_line [] = {
        EMPTY_TILE, EMPTY_TILE, EMPTY_TILE, EMPTY_TILE
    };
    uint16_t empty_slot [] = {
        OUTLINE_CARD + 0, OUTLINE_CARD + 1, OUTLINE_CARD + 1, OUTLINE_CARD + 2,
        OUTLINE_CARD + 3, EMPTY_TILE,       EMPTY_TILE,       OUTLINE_CARD + 4,
        OUTLINE_CARD + 3, EMPTY_TILE,       EMPTY_TILE,       OUTLINE_CARD + 4,
        OUTLINE_CARD + 3, EMPTY_TILE,       EMPTY_TILE,       OUTLINE_CARD + 4,
        OUTLINE_CARD + 3, EMPTY_TILE,       EMPTY_TILE,       OUTLINE_CARD + 4,
        OUTLINE_CARD + 5, OUTLINE_CARD + 6, OUTLINE_CARD + 6, OUTLINE_CARD + 7
    };
    uint16_t button_tiles [4];

    /* Dragons & Foundations*/
    for (uint8_t i = 0; i < 7; i++)
    {
        uint8_t col = (i < 3) ? i : i + 1;

        if (!stack_changed [8 + i])
        {
            continue;
        }

        if (stack [i + 8] [0] != 0xff)
        {
            uint8_t depth = top_card (i + 8);
            render_card_background (col, 1, stack [i + 8] [depth], false, false);
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

        if (!stack_changed [col])
        {
            continue;
        }

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

                render_card_background (col, 9 + depth, card, depth, next != 0xff);
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

    for (uint8_t i = 0; i < sizeof (stack_changed); i++)
    {
        if (stack_changed [i])
        {
            check_dragons ();
            break;
        }
    }

    /* Buttons */
    for (uint8_t i = 0; i < 3; i++)
    {
        button_tiles [0] = BUTTON_TILES + (i * 8) + (button_active [i] * 4);
        button_tiles [1] = BUTTON_TILES + (i * 8) + (button_active [i] * 4) + 1;
        button_tiles [2] = BUTTON_TILES + (i * 8) + (button_active [i] * 4) + 2;
        button_tiles [3] = BUTTON_TILES + (i * 8) + (button_active [i] * 4) + 3;

        SMS_loadTileMapArea (13, (i * 2) + 1, &button_tiles, 2, 2);
    }

    memset (stack_changed, false, sizeof (stack_changed));
}


/*
 * Deal a new game.
 */
void deal (void)
{
    uint8_t i;

    rng_seed ();

    for (i = 0; i < 16; i++)
    {
        stack [i] [0] = 0xff;

    }
    memset (stack_changed, true, sizeof (stack_changed));

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
    for (uint8_t depth = 0; depth < 5; depth++)
    {
        for (uint8_t col = 0; col < 8; col++)
        {
            stack [col] [depth] = deck [i++];
            stack [col] [depth + 1] = 0xff;
            stack_changed [col] = true;

            /* Poorly animated deal */
            SMS_waitForVBlank ();
            render_background ();
        }
    }

    cursor_stack = CURSOR_COLUMN_1;
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (PORT_A_KEY_DOWN);
}


/*
 * Fill the name table with tile-zero.
 */
void clear_background (void)
{
    uint16_t blank_line [32] = { 0 };

    for (uint8_t row = 0; row < 24; row++)
    {
        SMS_loadTileMapArea (0, row, &blank_line, 32, 1);
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
    clear_background ();

    SMS_useFirstHalfTilesforSprites (true);
    SMS_initSprites ();
    SMS_copySpritestoSAT ();

    SMS_displayOn ();

    sram_enable ();
    sram_read ();

    deal ();
    render_background ();

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
            if (stack [HELD] [0] == 0xff)
            {
                if (cursor_stack == CURSOR_DRAGON_BUTTONS)
                {
                    if (button_active [cursor_depth])
                    {
                        stack_dragons ();
                    }
                }
                else
                {
                    cursor_pick ();
                }
            }
            else
            {
                cursor_place ();
            }
        }
        else if (keys_pressed & PORT_A_KEY_2)
        {
            if (stack [HELD] [0] == 0xff)
            {
                uint8_t stack_idx = (cursor_stack < CURSOR_DRAGON_BUTTONS) ? cursor_stack : cursor_stack - 1;
                uint8_t _cursor_stack = cursor_stack;

                if (cursor_depth == top_card (stack_idx))
                {
                    cursor_pick ();

                    /* Try placing in each slot */
                    for (uint8_t i = CURSOR_FOUNDATION_SNEP; stack [HELD] [0] != 0xff && i <= CURSOR_FOUNDATION_3; i++)
                    {
                        cursor_stack = i;
                        cursor_depth = CURSOR_DEPTH_MAX;
                        cursor_move (PORT_A_KEY_DOWN);
                        cursor_place ();
                    }

                    /* Restore cursor position, returning the card if we still have it */
                    cursor_stack = _cursor_stack;
                    cursor_depth = CURSOR_DEPTH_MAX;
                    cursor_move (PORT_A_KEY_DOWN);
                    if (stack [HELD] [0] != 0xff)
                    {
                        cursor_place ();
                    }
                }
            }
            else
            {
                /* Cancel the currently held cards */
                cursor_stack = came_from;
                cursor_depth = CURSOR_DEPTH_MAX;
                cursor_move (PORT_A_KEY_DOWN);
                cursor_place ();
            }
        }

        keys_previous = keys;

        /* Render */
        SMS_waitForVBlank ();

        /* Update cards in background layer */
        render_background ();

        if (sprite_update)
        {
            SMS_copySpritestoSAT ();
            sprite_update = false;
        }
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
