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

#include "save.h"
#include "rng.h"

#include "../tile_data/pattern.h"
#include "../tile_data/pattern_index.h"
#include "../tile_data/palette.h"

/* Constants */
#define PORT_A_KEY_DPAD     (PORT_A_KEY_UP | PORT_A_KEY_DOWN | PORT_A_KEY_LEFT | PORT_A_KEY_RIGHT)
#define CARD_TYPE_MASK      0x30
#define CARD_VALUE_MASK     0x0f
#define STACK_HELD          15

bool sprite_update = false;
uint8_t cursor_style = 2;

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

    if (stack [s] [0] == 0xff)
    {
        return 0;
    }

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
 * Render a single card to an array of tile indexes.
 */
void render_card_tiles (uint16_t *buf, uint8_t card, bool stacked)
{
    uint8_t value = card & CARD_VALUE_MASK;
    uint8_t tile;

    uint16_t card_tiles [] = {
        PATTERN_CARD_BLANK +  0, PATTERN_CARD_BLANK +  2, PATTERN_CARD_BLANK +  2, PATTERN_CARD_BLANK +  3,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  9, PATTERN_CARD_BLANK + 10, PATTERN_CARD_BLANK + 10, PATTERN_CARD_BLANK + 11
    };

    if ((card & CARD_TYPE_MASK) == 0x30)
    {
        if (value == 3)
        {
            /* Snep card */
            card_tiles [0]  = PATTERN_CORNER_SNEP;
            card_tiles [23] = PATTERN_CORNER_SNEP + 2;

            for (uint8_t i = 0; i < 16; i++)
            {
                card_tiles [i + 4] = PATTERN_SNEP_CARD + i;
            }
        }
        else
        {
            /* Print card */
            card_tiles [0]  = PATTERN_CORNER_PRINTS + (value * 3);
            card_tiles [1]  = PATTERN_CORNER_PRINTS + (value * 3) + 2;

            tile = PATTERN_PRINTS + value * 4;
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
        tile = PATTERN_CORNER_NUMBERS + value * 6 + colour * 2;
        card_tiles [ 0] = tile;

        /* Chinese numbers */
        tile = PATTERN_CHINESE_NUMBERS + value * 12 + colour * 4;
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
 * Position specified as (x, y) coordinate.
 */
void cursor_render_xy (uint8_t cursor_x, uint8_t cursor_y, bool cursor_visible)
{
    /* Clear any previous sprites */
    SMS_initSprites ();

    if (cursor_visible)
    {
        SMS_addSprite (cursor_x,     cursor_y,     (uint8_t) (PATTERN_CURSOR + (4 * cursor_style)    ));
        SMS_addSprite (cursor_x + 8, cursor_y,     (uint8_t) (PATTERN_CURSOR + (4 * cursor_style) + 1));
        SMS_addSprite (cursor_x,     cursor_y + 8, (uint8_t) (PATTERN_CURSOR + (4 * cursor_style) + 2));
        SMS_addSprite (cursor_x + 8, cursor_y + 8, (uint8_t) (PATTERN_CURSOR + (4 * cursor_style) + 3));
    }

    /* Render held cards as sprites */
    if (stack [STACK_HELD] [0] != 0xff)
    {
        uint8_t card_x = cursor_x - 16;
        uint8_t top = top_card (STACK_HELD);

        for (uint8_t i = top; i != 0xff; i--)
        {
            uint16_t card_y = cursor_y + (8 * i) - 4;
            uint16_t card_tiles [24];

            render_card_tiles (card_tiles, stack [STACK_HELD] [i], i > 0);

            for (uint8_t y = 0; y < 6; y++)
            {
                uint16_t sprite_y = card_y + (8 * y);

                /* Don't draw sprites that are completely off screen */
                if (sprite_y > 192)
                {
                    continue;
                }

                for (uint8_t x = 0; x < 4; x++)
                {
                    SMS_addSprite (card_x + (8 * x), sprite_y, (uint8_t) card_tiles [x + (4 * y)]);
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
 * Convert cursor (stack, depth) coordinates into (x, y).
 */
void cursor_sd_to_xy (uint8_t stack, uint8_t depth, uint8_t *x, uint8_t *y)
{
    *x = (stack & 0x07) * 32 + 16;

    if (stack == CURSOR_DRAGON_BUTTONS)
    {
        *y = (depth * 16) + 16;
    }
    else if (stack > CURSOR_COLUMN_8)
    {
        *y = 12;
    }
    else
    {
        *y = (depth * 8) + 76;
    }
}


/*
 * Render the cursor and its held cards, as sprites.
 * Position specified as (stack, depth) coordinate.
 */
void cursor_render (void)
{
    uint8_t cursor_x;
    uint8_t cursor_y;

    cursor_sd_to_xy (cursor_stack, cursor_depth, &cursor_x, &cursor_y);

    /* Offset the cursor if we're holding a card */
    if (stack [STACK_HELD] [0] != 0xff)
    {
        cursor_x += 2;
        cursor_y += 12;
    }

    cursor_render_xy (cursor_x, cursor_y, true);
}


/*
 * Move the cursor one position up.
 */
void cursor_move_up (void)
{
    if (cursor_depth > 0 &&
            ((cursor_stack == CURSOR_DRAGON_BUTTONS) ||
             (cursor_stack <= CURSOR_COLUMN_8 && stack [STACK_HELD] [0] == 0xff)))
    {
        cursor_depth--;
    }
    else if (cursor_stack == CURSOR_COLUMN_4)
    {
        /* Special case for column below dragon cards:
         * Only jump if we aren't holding a card. Start on the bottom button. */
        if (stack [STACK_HELD] [0] == 0xff)
        {
            cursor_stack = CURSOR_DRAGON_BUTTONS;
            cursor_depth = 2;
        }
    }
    else if (cursor_stack <= CURSOR_COLUMN_8)
    {
        cursor_stack += 8;
    }
}


/*
 * Move the cursor one position down.
 */
void cursor_move_down (void)
{
    if (cursor_stack == CURSOR_DRAGON_BUTTONS)
    {
        if (cursor_depth == 2)
        {
            cursor_stack = CURSOR_COLUMN_4;
            cursor_depth = CURSOR_DEPTH_MAX;
        }
        else
        {
            cursor_depth++;
        }
    }
    else if (cursor_stack >= CURSOR_DRAGON_SLOT_1)
    {
        cursor_stack -= 8;
        cursor_depth = CURSOR_DEPTH_MAX;
    }
    else
    {
        cursor_depth++;
    }
}


/*
 * Move the cursor one position left.
 */
void cursor_move_left (void)
{
    cursor_stack = (cursor_stack + (CURSOR_STACK_MAX - 1)) % CURSOR_STACK_MAX;
    cursor_depth = CURSOR_DEPTH_MAX;

    if (cursor_stack == CURSOR_DRAGON_BUTTONS)
    {
        if (stack [STACK_HELD] [0] != 0xff)
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
}


/*
 * Move the cursor one position right.
 */
void cursor_move_right (void)
{
    cursor_stack = (cursor_stack + 1) % CURSOR_STACK_MAX;
    cursor_depth = CURSOR_DEPTH_MAX;

    /* Skip over the buttons if holding a card */
    if (cursor_stack == CURSOR_DRAGON_BUTTONS)
    {
        if (stack [STACK_HELD] [0] != 0xff)
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
}


/*
 * Calculate the new cursor position after d-pad input.
 */
void cursor_move (uint8_t direction)
{
    uint8_t stack_max_depth = 0;
    uint8_t stack_idx;

    if (direction == PORT_A_KEY_UP)
    {
        cursor_move_up ();
    }
    else if (direction == PORT_A_KEY_DOWN)
    {
        cursor_move_down ();
    }
    else if (direction == PORT_A_KEY_LEFT)
    {
        cursor_move_left ();
    }
    else if (direction == PORT_A_KEY_RIGHT)
    {
        cursor_move_right ();
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
            if ((card & CARD_TYPE_MASK) == 0x30)
            {
                return;
            }

            if (i > 0)
            {
                if (cursor_stack <= CURSOR_COLUMN_8)
                {
                    /* Colours must alternate */
                    if ((card & CARD_TYPE_MASK) == (previous_card & CARD_TYPE_MASK))
                    {
                        return;
                    }

                    /* Value must decrease */
                    if ((card & CARD_VALUE_MASK) != (previous_card & CARD_VALUE_MASK) - 1)
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
        stack [STACK_HELD] [i] = stack [stack_idx] [cursor_depth + i];
        stack [stack_idx] [cursor_depth + i] = 0xff;
    }
    stack [STACK_HELD] [i] = 0xff;
    stack_changed [stack_idx] = true;

    came_from = cursor_stack;

    /* Point at the new top card in the stack */
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (0);
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
                if (((stack_card             & 0x30) == 0x30) ||
                    ((stack [STACK_HELD] [0] & 0x30) == 0x30))
                {
                    return;
                }

                /* Colours must alternate */
                if ((stack_card & 0x30) == (stack [STACK_HELD] [0] & 0x30))
                {
                    return;
                }

                /* Value must decrease */
                if ((stack_card & CARD_VALUE_MASK) != (stack [STACK_HELD] [0] & CARD_VALUE_MASK) + 1)
                {
                    return;
                }
            }
        }
        else if (cursor_stack <= CURSOR_DRAGON_SLOT_3)
        {
            /* Only single cards may be placed in the dragon slots */
            if ((stack_card != 0xff) || (stack [STACK_HELD] [1] != 0xff))
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
            if (stack [STACK_HELD] [0] != 0x33)
            {
                return;
            }
        }
        else if (cursor_stack <= CURSOR_FOUNDATION_3)
        {
            /* No special cards, and only one card at a time */
            if ((stack [STACK_HELD] [0] & CARD_TYPE_MASK) == 0x30 || stack [STACK_HELD] [1] != 0xff)
            {
                return;
            }

            /* Only a '1' can be placed on an empty slot */
            if (stack [stack_idx] [0] == 0xff)
            {
                if ((stack [STACK_HELD] [0] & CARD_VALUE_MASK) != 0)
                {
                    return;
                }
            }
            else
            {
                /* Cards in a foundation must all be the same colour */
                if ((stack_card & CARD_TYPE_MASK) != (stack [STACK_HELD] [0] & CARD_TYPE_MASK))
                {
                    return;
                }
                /* Cards in a foundation must be in increasing order */
                if ((stack_card & CARD_VALUE_MASK) != (stack [STACK_HELD] [0] & CARD_VALUE_MASK) - 1)
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
    for (i = 0; stack [STACK_HELD] [i] != 0xff; i++)
    {
        stack [stack_idx] [cursor_depth + i] = stack [STACK_HELD] [i];
        stack [STACK_HELD] [i] = 0xff;
    }
    stack [stack_idx] [cursor_depth + i] = 0xff;
    stack_changed [stack_idx] = true;

    came_from = 0xff;

    /* Point at the new top card in the stack */
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (0);
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
        PATTERN_EMPTY, PATTERN_EMPTY, PATTERN_EMPTY, PATTERN_EMPTY
    };
    uint16_t empty_slot [] = {
        PATTERN_CARD_OUTLINE + 0, PATTERN_CARD_OUTLINE + 1, PATTERN_CARD_OUTLINE + 1, PATTERN_CARD_OUTLINE + 2,
        PATTERN_CARD_OUTLINE + 3, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 5,
        PATTERN_CARD_OUTLINE + 3, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 5,
        PATTERN_CARD_OUTLINE + 3, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 5,
        PATTERN_CARD_OUTLINE + 3, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 4, PATTERN_CARD_OUTLINE + 5,
        PATTERN_CARD_OUTLINE + 6, PATTERN_CARD_OUTLINE + 7, PATTERN_CARD_OUTLINE + 7, PATTERN_CARD_OUTLINE + 8
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
        button_tiles [0] = PATTERN_DRAGON_BUTTONS + (i * 8) + (button_active [i] * 4);
        button_tiles [1] = PATTERN_DRAGON_BUTTONS + (i * 8) + (button_active [i] * 4) + 1;
        button_tiles [2] = PATTERN_DRAGON_BUTTONS + (i * 8) + (button_active [i] * 4) + 2;
        button_tiles [3] = PATTERN_DRAGON_BUTTONS + (i * 8) + (button_active [i] * 4) + 3;

        SMS_loadTileMapArea (13, (i * 2) + 1, &button_tiles, 2, 2);
    }

    memset (stack_changed, false, sizeof (stack_changed));
}


/*
 * Animate a card sliding from one position to another.
 */
void card_slide (uint16_t start_x, uint16_t start_y,
                 uint16_t end_x,   uint16_t end_y,
                 uint8_t frames,   bool cursor_visible)
{
    uint16_t x;
    uint16_t y;

    for (uint8_t frame = 1; frame < frames; frame++)
    {
        /* Calculate next position */
        x = (((start_x * 8) * (frames - frame)) +
             ((end_x   * 8) * (         frame))) / frames / 8;
        y = (((start_y * 8) * (frames - frame)) +
             ((end_y   * 8) * (         frame))) / frames / 8;

        cursor_render_xy (x, y, cursor_visible);

        /* Write to hardware */
        SMS_waitForVBlank ();
        SMS_copySpritestoSAT ();
    }

    SMS_initSprites ();
    SMS_copySpritestoSAT ();
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
    render_background ();

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
    stack [STACK_HELD] [1] = 0xff;
    for (uint8_t depth = 0; depth < 5; depth++)
    {
        for (uint8_t col = 0; col < 8; col++)
        {
            uint8_t dest_x;
            uint8_t dest_y;

            cursor_sd_to_xy (col, depth, &dest_x, &dest_y);

            /* Animate the card being dealt */
            stack [STACK_HELD] [0] = deck [i];
            card_slide (dest_x, 192, dest_x, dest_y, 8, false);
            stack [STACK_HELD] [0] = 0xff;

            /* Store the card in its new position */
            stack [col] [depth] = deck [i++];
            stack [col] [depth + 1] = 0xff;
            stack_changed [col] = true;

            render_background ();
        }
    }

    cursor_stack = CURSOR_COLUMN_1;
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (0);
}


/*
 * Undeal the cards (winning animation).
 */
void undeal (void)
{
    bool cards_left = true;
    stack [STACK_HELD] [1] = 0xff;

    while (cards_left)
    {
        cards_left = false;

        for (uint8_t col = CURSOR_DRAGON_SLOT_1; col <= CURSOR_FOUNDATION_3; col++)
        {
            uint8_t stack_idx = (col < CURSOR_DRAGON_BUTTONS) ? col : col - 1;
            uint8_t from_x;
            uint8_t from_y;
            uint8_t top;

            if (col == CURSOR_DRAGON_BUTTONS)
            {
                continue;
            }

            top = top_card (stack_idx);

            if (stack [stack_idx] [top] == 0xff)
            {
                continue;
            }

            cards_left = true;

            cursor_sd_to_xy (col, top, &from_x, &from_y);

            /* Animate the card being removed */
            stack [STACK_HELD] [0] = stack [stack_idx] [top];
            stack [stack_idx] [top] = 0xff;
            stack_changed [stack_idx] = true;

            render_background ();
            card_slide (from_x, from_y, from_x, 192, 8, false);

            stack [STACK_HELD] [0] = 0xff;
        }
    }
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
 * Stack four dragon cards into a slot.
 */
void stack_dragons (void)
{
    uint8_t from_x;
    uint8_t from_y;
    uint8_t to_x;
    uint8_t to_y;

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

    /* Animation end-point */
    cursor_sd_to_xy (dest_idx, 0, &to_x, &to_y);
    stack [STACK_HELD] [0] = card_match;
    stack [STACK_HELD] [1] = 0xff;

    /* Remove the dragons from wherever they may be */
    for (uint8_t stack_idx = 0; stack_idx <= CURSOR_DRAGON_SLOT_3; stack_idx++)
    {
        uint8_t top = top_card (stack_idx);

        if (stack [stack_idx] [top] == card_match)
        {
            /* Animation start-point */
            cursor_sd_to_xy (stack_idx, top, &from_x, &from_y);

            stack [stack_idx] [top] = 0xff;
            stack_changed [stack_idx] = true;
            render_background ();

            card_slide (from_x, from_y, to_x, to_y, 10, false);

            /* If there are currently no cards in the destination, draw one after the first slide-animation */
            if (stack [dest_idx] [0] == 0xff)
            {
                stack [dest_idx] [0] = card_match;
                stack [dest_idx] [1] = 0xff;
                stack_changed [dest_idx] = true;
                render_background ();
            }
        }
    }

    stack [STACK_HELD] [0] = 0xff;

    /* Place all four dragons into the destination slot */
    for (uint8_t i = 0; i < 4; i++)
    {
        stack [dest_idx] [i] = card_match;
    }
    stack [dest_idx] [4] = 0xff;
}


/*
 * Move the currently-selected card to the foundation if possible.
 */
void move_auto (void)
{
    uint8_t from_x;
    uint8_t from_y;
    uint8_t to_x;
    uint8_t to_y;

    uint8_t from_stack = cursor_stack;

    /* If we're already pointing at a foundation, there is nothing to do */
    if (from_stack >= CURSOR_FOUNDATION_SNEP)
    {
        return;
    }

    /* Only the top card in a stack can be auto-moved */
    if (cursor_depth != top_card (from_stack))
    {
        return;
    }

    /* Animation start-point */
    cursor_sd_to_xy (from_stack, cursor_depth, &from_x, &from_y);

    cursor_pick ();

    /* Abort if there wasn't actually a card */
    if (stack [STACK_HELD] [0] == 0xff)
    {
        return;
    }

    /* Try placing in each slot */
    for (uint8_t i = CURSOR_FOUNDATION_SNEP; i <= CURSOR_FOUNDATION_3; i++)
    {
        cursor_stack = i;
        cursor_depth = CURSOR_DEPTH_MAX;
        cursor_move (0);
        cursor_place ();

        /* Placement was successful */
        if (stack [STACK_HELD] [0] == 0xff)
        {
            /* Animation end-point */
            cursor_sd_to_xy (cursor_stack, cursor_depth, &to_x, &to_y);

            cursor_pick ();
            render_background ();
            card_slide (from_x, from_y, to_x, to_y, 10, false);
            cursor_place ();
            render_background ();
            break;
        }
    }

    /* Restore cursor position, returning the card if we still have it */
    cursor_stack = from_stack;
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (0);
    if (stack [STACK_HELD] [0] != 0xff)
    {
        cursor_place ();
    }
}


/*
 * Cancel the current card movement, returning to where it came from.
 */
void move_cancel (void)
{
    uint8_t from_x;
    uint8_t from_y;
    uint8_t to_x;
    uint8_t to_y;

    /* Animation start-point */
    cursor_sd_to_xy (cursor_stack, cursor_depth, &from_x, &from_y);

    cursor_stack = came_from;
    cursor_depth = CURSOR_DEPTH_MAX;
    cursor_move (0);

    /* Animation end-point*/
    cursor_sd_to_xy (cursor_stack, cursor_depth + 1, &to_x, &to_y);

    card_slide (from_x + 2, from_y + 12, to_x, to_y, 10, true);
    cursor_place ();

    /* Update the background early, to avoid a frame without the card */
    render_background ();
}


/*
 * Play one game.
 */
void game (void)
{
    bool playing = true;

    while (playing)
    {
        static uint16_t keys_previous = 0;
        uint16_t keys = SMS_getKeysStatus ();
        uint16_t keys_pressed = (keys & ~keys_previous);

        /* Logic */
        if (keys_pressed & PORT_A_KEY_DPAD)
        {
            cursor_move (keys_pressed);
        }

        if (keys_pressed & PORT_A_KEY_1)
        {
            if (stack [STACK_HELD] [0] == 0xff)
            {
                if (cursor_stack == CURSOR_DRAGON_BUTTONS)
                {
                    if (button_active [cursor_depth])
                    {
                        stack_dragons ();
                        cursor_move (0);
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
            if (cursor_stack == CURSOR_DRAGON_BUTTONS)
            {
                /* Do nothing */
            }
            else if (stack [STACK_HELD] [0] == 0xff)
            {
                move_auto ();
            }
            else
            {
                move_cancel ();
            }
        }

        keys_previous = keys;

        /* Update H/W during vblank */
        SMS_waitForVBlank ();

        if (sprite_update)
        {
            SMS_copySpritestoSAT ();
            sprite_update = false;
        }
        render_background ();

        /* Check if the game is still in progress */
        playing = false;
        for (uint8_t i = 0; i <= CURSOR_COLUMN_8; i++)
        {
            if (stack [i] [0] != 0xff)
            {
                playing = true;
            }
        }
        if (stack [STACK_HELD] [0] != 0xff)
        {
            playing = true;
        }
    }
}


/*
 * Cycle through different colour schemes.
 */
void next_palette (void)
{
    /* Start on dark-green */
    static uint8_t index = 1;

    index = (index + 1) % 8;

    switch (index)
    {
        case 0: /* Dark Red */
            SMS_setSpritePaletteColor (0, 0x01); /* Dark Red */
            SMS_setBGPaletteColor     (0, 0x01); /* Dark Red */
            SMS_setBGPaletteColor     (1, 0x16); /* Brick*/
            break;
        case 1: /* Dark Green */
            SMS_setSpritePaletteColor (0, 0x04); /* Dark Green */
            SMS_setBGPaletteColor     (0, 0x04); /* Dark Green */
            SMS_setBGPaletteColor     (1, 0x19); /* Light Green */
            break;
        case 2: /* Dark Blue */
            SMS_setSpritePaletteColor (0, 0x10); /* Dark Blue */
            SMS_setBGPaletteColor     (0, 0x10); /* Dark Blue */
            SMS_setBGPaletteColor     (1, 0x24); /* Light Blue */
            break;
        case 3: /* Dark */
            SMS_setSpritePaletteColor (0, 0x15); /* Dark Grey */
            SMS_setBGPaletteColor     (0, 0x15); /* Dark Grey */
            SMS_setBGPaletteColor     (1, 0x2a); /* Light Grey */
            break;
        case 4: /* Light Red */
            SMS_setSpritePaletteColor (0, 0x16); /* Light Red */
            SMS_setBGPaletteColor     (0, 0x16); /* Light Red */
            SMS_setBGPaletteColor     (1, 0x01); /* Dark Red*/
            break;
        case 5: /* Light Green */
            SMS_setSpritePaletteColor (0, 0x19); /* Light Green */
            SMS_setBGPaletteColor     (0, 0x19); /* Light Green */
            SMS_setBGPaletteColor     (1, 0x04); /* Dark Green */
            break;
        case 6: /* Light Blue */
            SMS_setSpritePaletteColor (0, 0x24); /* Light Blue */
            SMS_setBGPaletteColor     (0, 0x24); /* Light Blue */
            SMS_setBGPaletteColor     (1, 0x10); /* Dark Blue */
            break;
        case 7: /* Light */
            SMS_setSpritePaletteColor (0, 0x2a); /* Light Grey */
            SMS_setBGPaletteColor     (0, 0x2a); /* Light Grey */
            SMS_setBGPaletteColor     (1, 0x15); /* Dark Grey */
            break;
    }
}


/*
 * Main menu.
 */
void menu (void)
{
    bool in_menu = true;
    uint16_t card_tiles [] = {
        PATTERN_CARD_BLANK +  0, PATTERN_CARD_BLANK +  2, PATTERN_CARD_BLANK +  2, PATTERN_CARD_BLANK +  3,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  5, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  6, PATTERN_CARD_BLANK +  7,
        PATTERN_CARD_BLANK +  9, PATTERN_CARD_BLANK + 10, PATTERN_CARD_BLANK + 10, PATTERN_CARD_BLANK + 11
    };

    /* Render background */
    memset (stack_changed, true, sizeof (stack_changed));
    render_background ();
    cursor_stack = 2;
    cursor_depth = 0;
    cursor_render ();

    /* Render menu cards */
    for (uint8_t i = 0; i < 3; i++)
    {
        uint16_t tile = PATTERN_MENU_TEXT + (4 * i);
        card_tiles [4] = tile;
        card_tiles [5] = tile + 1;
        card_tiles [6] = tile + 2;
        card_tiles [7] = tile + 3;

        tile = PATTERN_MENU_ICONS + (4 * i);
        card_tiles [13] = tile;
        card_tiles [14] = tile + 1;
        card_tiles [17] = tile + 2;
        card_tiles [18] = tile + 3;

        SMS_loadTileMapArea (4 * (i + 2), 9, &card_tiles, 4, 6);
    }

    while (in_menu)
    {
        static uint16_t keys_previous = 0;
        uint16_t keys = SMS_getKeysStatus ();
        uint16_t keys_pressed = (keys & ~keys_previous);

        /* Logic */
        if (keys_pressed & PORT_A_KEY_DPAD)
        {
            cursor_move (keys_pressed);
        }

        if (keys_pressed & PORT_A_KEY_1)
        {
            /* Start */
            if (cursor_stack == 2)
            {
                in_menu = false;
            }
            /* Table */
            else if (cursor_stack == 3)
            {
                next_palette ();
            }
            /* Arrow */
            else if (cursor_stack == 4)
            {
                cursor_style = (cursor_style + 1) % 3;
                cursor_render ();
            }
        }

        keys_previous = keys;

        SMS_waitForVBlank ();

        if (sprite_update)
        {
            SMS_copySpritestoSAT ();
            sprite_update = false;
        }
    }

    memset (stack_changed, true, sizeof (stack_changed));
    render_background ();
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

    sram_load ();

    menu ();

    /* Main loop */
    while (true)
    {
        deal ();
        game ();
        undeal ();
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
