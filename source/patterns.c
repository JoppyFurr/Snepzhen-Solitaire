
#define EMPTY_TILE        0
#define CURSOR_BLACK      1
#define CURSOR_SILVER     5
#define CURSOR_WHITE      9
#define BLANK_CARD       13
#define CORNER_NUMBERS   24
#define CORNER_PRINTS    78
#define CORNER_SNEP      87
#define ARTWORK_NUMBERS  90
#define ARTWORK_PRINTS  198
#define ARTWORK_SNEP    210
#define OUTLINE_CARD    226
#define BUTTON_TILES    234

/* Patterns */
const uint32_t patterns [] = {

    /* Empty tile */
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x00000000,

    /*
     * Cursors.
     */

    /* Cursor (black) top-left */
    0x0000c0c0,     0x0000e0a0,     0x0000f090,     0x0000f888,
    0x0000fc84,     0x0000fe82,     0x0000ff81,     0x0000ff80,
    /* Cursor (black) top-right */
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x00008080,
    /* Cursor (black) bottom-left */
    0x0000ff80,     0x0000ff83,     0x0000fe92,     0x0000efa9,
    0x0000cfc9,     0x00008784,     0x00000704,     0x00000303,
    /* Cursor (black) bottom-right */
    0x0000c040,     0x0000e0e0,     0x00000000,     0x00000000,
    0x00000000,     0x00008080,     0x00008080,     0x00008080,

    /* Cursor (silver) top-left */
    0x00008000,     0x0080c080,     0x00c0e080,     0x00e0f080,
    0x00b0f8c0,     0x00b8fcc0,     0x009cfee0,     0x009effe0,
    /* Cursor (silver) top-right */
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    /* Cursor (silver) bottom-left */
    0x008ffff0,     0x0090ffe0,     0x00a4fec8,     0x00caef8c,
    0x008acf8c,     0x00058706,     0x00070704,     0x00000300,
    /* Cursor (silver) bottom-right */
    0x00008000,     0x0000c000,     0x00000000,     0x00000000,
    0x00000000,     0x00008000,     0x00008000,     0x00008000,

    /* Cursor (white) top-left */
    0x0000c000,     0x0000e040,     0x0000f060,     0x0000f870,
    0x0000fc78,     0x0000fe7c,     0x0000ff7e,     0x0000ff7f,
    /* Cursor (white) top-right */
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x00008000,
    /* Cursor (white) bottom-left */
    0x0000ff7f,     0x0000ff7c,     0x0000fe6c,     0x0000ef46,
    0x0000cf06,     0x00008703,     0x00000703,     0x00000300,
    /* Cursor (white) bottom-right */
    0x0000c080,     0x0000e000,     0x00000000,     0x00000000,
    0x00000000,     0x00008000,     0x00008000,     0x00008000,

    /*
     * 13 - Blank card.
     */

    /* Card top-left */
    0x00000700,     0x00000f07,     0x00001f0f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Card top-left stacked */
    0x00003f18,     0x00003f17,     0x00003f0f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Card top-edge */
    0x0000ff00,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Card top-right */
    0x0000e000,     0x0000f0e0,     0x0000f8f0,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    /* Card top-right stacked */
    0x0000fc18,     0x0000fce8,     0x0000fcf0,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    /* Card left-edge */
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Card blank-middle */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Card right-edge */
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    /* Card bottom-left */
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    0x00003f1f,     0x00001f0f,     0x00000f07,     0x00000700,
    /* Card bottom-edge */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff00,
    /* Card bottom-right */
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000f8f0,     0x0000f0e0,     0x0000e000,

    /*
     * 24 Card-corner numbers.
     */

    /* One (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f0d,     0x00003f19,
    0x00003f1d,     0x00003f1d,     0x00003f18,     0x00003f1f,
    /* One (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f0d,     0x00003f19,
    0x00003f1d,     0x00003f1d,     0x00003f18,     0x00003f1f,
    /* One (red) on-felt */
    0x00000700,     0x00000f07,     0x00021d0d,     0x00063919,
    0x00023d1d,     0x00023d1d,     0x00073818,     0x00003f1f,
    /* One (red) on-card */
    0x00003f18,     0x00003f17,     0x00023d0d,     0x00063919,
    0x00023d1d,     0x00023d1d,     0x00073818,     0x00003f1f,
    /* One (green) on-felt */
    0x00000700,     0x00000f07,     0x00021d0f,     0x0006391f,
    0x00023d1f,     0x00023d1f,     0x0007381f,     0x00003f1f,
    /* One (green) on-card */
    0x00003f18,     0x00003f17,     0x00023d0f,     0x0006391f,
    0x00023d1f,     0x00023d1f,     0x0007381f,     0x00003f1f,

    /* Two (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f09,     0x00003f1e,
    0x00003f18,     0x00003f1b,     0x00003f18,     0x00003f1f,
    /* Two (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f09,     0x00003f1e,
    0x00003f18,     0x00003f1b,     0x00003f18,     0x00003f1f,
    /* Two (red) on-felt */
    0x00000700,     0x00000f07,     0x00061909,     0x00013e1e,
    0x00073818,     0x00043b1b,     0x00073818,     0x00003f1f,
    /* Two (red) on-card */
    0x00003f18,     0x00003f17,     0x00063909,     0x00013e1e,
    0x00073818,     0x00043b1b,     0x00073818,     0x00003f1f,
    /* Two (green) on-felt */
    0x00000700,     0x00000f07,     0x0006190f,     0x00013e1f,
    0x0007381f,     0x00043b1f,     0x0007381f,     0x00003f1f,
    /* Two (green) on-card */
    0x00003f18,     0x00003f17,     0x0006390f,     0x00013e1f,
    0x0007381f,     0x00043b1f,     0x0007381f,     0x00003f1f,

    /* Three (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f08,     0x00003f1e,
    0x00003f1c,     0x00003f1e,     0x00003f18,     0x00003f1f,
    /* Three (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f08,     0x00003f1e,
    0x00003f1c,     0x00003f1e,     0x00003f18,     0x00003f1f,
    /* Three (red) on-felt */
    0x00000700,     0x00000f07,     0x00071808,     0x00013e1e,
    0x00033c1c,     0x00013e1e,     0x00073818,     0x00003f1f,
    /* Three (red) on-card */
    0x00003f18,     0x00003f17,     0x00073808,     0x00013e1e,
    0x00033c1c,     0x00013e1e,     0x00073818,     0x00003f1f,
    /* Three (green) on-felt */
    0x00000700,     0x00000f07,     0x0007180f,     0x00013e1f,
    0x00033c1f,     0x00013e1f,     0x0007381f,     0x00003f1f,
    /* Three (green) on-card */
    0x00003f18,     0x00003f17,     0x0007380f,     0x00013e1f,
    0x00033c1f,     0x00013e1f,     0x0007381f,     0x00003f1f,

    /* Four (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f0a,     0x00003f1a,
    0x00003f18,     0x00003f1e,     0x00003f1e,     0x00003f1f,
    /* Four (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f0a,     0x00003f1a,
    0x00003f18,     0x00003f1e,     0x00003f1e,     0x00003f1f,
    /* Four (red) on-felt */
    0x00000700,     0x00000f07,     0x00051a0a,     0x00053a1a,
    0x00073818,     0x00013e1e,     0x00013e1e,     0x00003f1f,
    /* Four (red) on-card */
    0x00003f18,     0x00003f17,     0x00053a0a,     0x00053a1a,
    0x00073818,     0x00013e1e,     0x00013e1e,     0x00003f1f,
    /* Four (green) on-felt */
    0x00000700,     0x00000f07,     0x00051a0f,     0x00053a1f,
    0x0007381f,     0x00013e1f,     0x00013e1f,     0x00003f1f,
    /* Four (green) on-card */
    0x00003f18,     0x00003f17,     0x00053a0f,     0x00053a1f,
    0x0007381f,     0x00013e1f,     0x00013e1f,     0x00003f1f,

    /* Five (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f08,     0x00003f1b,
    0x00003f18,     0x00003f1e,     0x00003f19,     0x00003f1f,
    /* Five (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f08,     0x00003f1b,
    0x00003f18,     0x00003f1e,     0x00003f19,     0x00003f1f,
    /* Five (red) on-felt */
    0x00000700,     0x00000f07,     0x00071808,     0x00043b1b,
    0x00073818,     0x00013e1e,     0x00063919,     0x00003f1f,
    /* Five (red) on-card */
    0x00003f18,     0x00003f17,     0x00073808,     0x00043b1b,
    0x00073818,     0x00013e1e,     0x00063919,     0x00003f1f,
    /* Five (green) on-felt */
    0x00000700,     0x00000f07,     0x0007180f,     0x00043b1f,
    0x0007381f,     0x00013e1f,     0x0006391f,     0x00003f1f,
    /* Five (green) on-card */
    0x00003f18,     0x00003f17,     0x0007380f,     0x00043b1f,
    0x0007381f,     0x00013e1f,     0x0006391f,     0x00003f1f,

    /* Six (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f0c,     0x00003f1b,
    0x00003f18,     0x00003f1a,     0x00003f18,     0x00003f1f,
    /* Six (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f0c,     0x00003f1b,
    0x00003f18,     0x00003f1a,     0x00003f18,     0x00003f1f,
    /* Six (red) on-felt */
    0x00000700,     0x00000f07,     0x00031c0c,     0x00043b1b,
    0x00073818,     0x00053a1a,     0x00073818,     0x00003f1f,
    /* Six (red) on-card */
    0x00003f18,     0x00003f17,     0x00033c0c,     0x00043b1b,
    0x00073818,     0x00053a1a,     0x00073818,     0x00003f1f,
    /* Six (green) on-felt */
    0x00000700,     0x00000f07,     0x00031c0f,     0x00043b1f,
    0x0007381f,     0x00053a1f,     0x0007381f,     0x00003f1f,
    /* Six (green) on-card */
    0x00003f18,     0x00003f17,     0x00033c0f,     0x00043b1f,
    0x0007381f,     0x00053a1f,     0x0007381f,     0x00003f1f,

    /* Seven (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f08,     0x00003f1e,
    0x00003f1d,     0x00003f1d,     0x00003f1d,     0x00003f1f,
    /* Seven (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f08,     0x00003f1e,
    0x00003f1d,     0x00003f1d,     0x00003f1d,     0x00003f1f,
    /* Seven (red) on-felt */
    0x00000700,     0x00000f07,     0x00071808,     0x00013e1e,
    0x00023d1d,     0x00023d1d,     0x00023d1d,     0x00003f1f,
    /* Seven (red) on-card */
    0x00003f18,     0x00003f17,     0x00073808,     0x00013e1e,
    0x00023d1d,     0x00023d1d,     0x00023d1d,     0x00003f1f,
    /* Seven (green) on-felt */
    0x00000700,     0x00000f07,     0x0007180f,     0x00013e1f,
    0x00023d1f,     0x00023d1f,     0x00023d1f,     0x00003f1f,
    /* Seven (green) on-card */
    0x00003f18,     0x00003f17,     0x0007380f,     0x00013e1f,
    0x00023d1f,     0x00023d1f,     0x00023d1f,     0x00003f1f,

    /* Eight (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f08,     0x00003f1a,
    0x00003f18,     0x00003f1a,     0x00003f18,     0x00003f1f,
    /* Eight (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f08,     0x00003f1a,
    0x00003f18,     0x00003f1a,     0x00003f18,     0x00003f1f,
    /* Eight (red) on-felt */
    0x00000700,     0x00000f07,     0x00071808,     0x00053a1a,
    0x00073818,     0x00053a1a,     0x00073818,     0x00003f1f,
    /* Eight (red) on-card */
    0x00003f18,     0x00003f17,     0x00073808,     0x00053a1a,
    0x00073818,     0x00053a1a,     0x00073818,     0x00003f1f,
    /* Eight (green) on-felt */
    0x00000700,     0x00000f07,     0x0007180f,     0x00053a1f,
    0x0007381f,     0x00053a1f,     0x0007381f,     0x00003f1f,
    /* Eight (green) on-card */
    0x00003f18,     0x00003f17,     0x0007380f,     0x00053a1f,
    0x0007381f,     0x00053a1f,     0x0007381f,     0x00003f1f,

    /* Nine (black) on-felt */
    0x00000700,     0x00000f07,     0x00001f08,     0x00003f1a,
    0x00003f18,     0x00003f1e,     0x00003f1e,     0x00003f1f,
    /* Nine (black) on-card */
    0x00003f18,     0x00003f17,     0x00003f08,     0x00003f1a,
    0x00003f18,     0x00003f1e,     0x00003f1e,     0x00003f1f,
    /* Nine (red) on-felt */
    0x00000700,     0x00000f07,     0x00071808,     0x00053a1a,
    0x00073818,     0x00013e1e,     0x00013e1e,     0x00003f1f,
    /* Nine (red) on-card */
    0x00003f18,     0x00003f17,     0x00073808,     0x00053a1a,
    0x00073818,     0x00013e1e,     0x00013e1e,     0x00003f1f,
    /* Nine (green) on-felt */
    0x00000700,     0x00000f07,     0x0007180f,     0x00053a1f,
    0x0007381f,     0x00013e1f,     0x00013e1f,     0x00003f1f,
    /* Nine (green) on-card */
    0x00003f18,     0x00003f17,     0x0007380f,     0x00053a1f,
    0x0007381f,     0x00013e1f,     0x00013e1f,     0x00003f1f,

    /*
     * 78 - Card-corner prints.
     */

    /* Claw (black) on-felt left */
    0x00000700,     0x00000f07,     0x00001f0e,     0x00003f1e,
    0x00003f1a,     0x00003f1c,     0x00003f1e,     0x00003f1f,
    /* Claw (black) on-card left */
    0x00003f18,     0x00003f17,     0x00003f0e,     0x00003f1e,
    0x00003f1a,     0x00003f1c,     0x00003f1e,     0x00003f1f,
    /* Claw (black) right */
    0x0000ff00,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffbf,     0x0000ff7f,     0x0000ffff,     0x0000ffff,

    /* Paw (red) on-felt left */
    0x00000700,     0x00000f07,     0x00011e0e,     0x00043b1b,
    0x00013e1e,     0x00033c1c,     0x00033c1c,     0x00003f1f,
    /* Paw (red) on-card left */
    0x00003f18,     0x00003f17,     0x00013e0e,     0x00043b1b,
    0x00013e1e,     0x00033c1c,     0x00033c1c,     0x00003f1f,
    /* Paw (red) right */
    0x0000ff00,     0x0000ffff,     0x0000ffff,     0x0040bfbf,
    0x0000ffff,     0x00807f7f,     0x00807f7f,     0x0000ffff,

    /* Hoof (green) on-felt left */
    0x00000700,     0x00000f07,     0x00021d0f,     0x0006391f,
    0x0006391f,     0x00003f1f,     0x00023d1f,     0x00003f1f,
    /* Hoof (green) on-card left */
    0x00003f18,     0x00003f17,     0x00023d0f,     0x0006391f,
    0x0006391f,     0x00003f1f,     0x00023d1f,     0x00003f1f,
    /* Hoof (green) right */
    0x0000ff00,     0x0000ffff,     0x00807fff,     0x00c03fff,
    0x00c03fff,     0x0000ffff,     0x00807fff,     0x0000ffff,

    /*
     * 87 - Card-corner snep.
     */

    /* Snep on-felt*/
    0x00000700,     0x00000f07,     0x00001f0f,     0x00063f1f,
    0x000f3f19,     0x000f3f19,     0x000f3f19,     0x000f3f19,
    /* Snep on-card*/
    0x00003f18,     0x00003f17,     0x00003f0f,     0x00063f1f,
    0x000f3f19,     0x000f3f19,     0x000f3f19,     0x000f3f19,
    /* Snep on-felt flipped*/
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000f8f0,     0x0000f0e0,     0x0000e000,

    /*
     * 90 - Chinese characters are Gnu Unifont at 16 × 16 pixels.
     */

    /* One (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff00,
    /* One (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff01,
    /* One (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* One (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* One (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00ff0000,
    /* One (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00fe0101,
    /* One (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* One (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* One (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00ff00ff,
    /* One (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00fe01ff,
    /* One (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* One (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,

    /* Two (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffc0,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff07,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff00,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff01,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0c0,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f80707,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00ff0000,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00fe0101,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0ff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f807ff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00ff00ff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Two (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00fe01ff,     0x0000ffff,     0x0000ffff,     0x0000ffff,

    /* Three (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ff80,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffc0,
    /* Three (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff03,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff07,
    /* Three (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff00,     0x0000ffff,     0x0000ffff,
    /* Three (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff01,     0x0000ffff,     0x0000ffff,
    /* Three (red) top-left */
    0x0000ffff,     0x0000ffff,     0x007f8080,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0c0,
    /* Three (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc0303,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f80707,
    /* Three (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff0000,     0x0000ffff,     0x0000ffff,
    /* Three (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00fe0101,     0x0000ffff,     0x0000ffff,
    /* Three (green) top-left */
    0x0000ffff,     0x0000ffff,     0x007f80ff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0ff,
    /* Three (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc03ff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f807ff,
    /* Three (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff00ff,     0x0000ffff,     0x0000ffff,
    /* Three (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00fe01ff,     0x0000ffff,     0x0000ffff,

    /* Four (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ff80,     0x0000ffbb,
    0x0000ffbb,     0x0000ffbb,     0x0000ffbb,     0x0000ffbb,
    /* Four (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff03,     0x0000ffbb,
    0x0000ffbb,     0x0000ffbb,     0x0000ffbb,     0x0000ffbb,
    /* Four (black) bottom-left */
    0x0000ffb7,     0x0000ffb7,     0x0000ffaf,     0x0000ff9f,
    0x0000ffbf,     0x0000ff80,     0x0000ffbf,     0x0000ffff,
    /* Four (black) bottom-right */
    0x0000ffbb,     0x0000ffc3,     0x0000fffb,     0x0000fffb,
    0x0000fffb,     0x0000ff03,     0x0000fffb,     0x0000ffff,
    /* Four (red) top-left */
    0x0000ffff,     0x0000ffff,     0x007f8080,     0x0044bbbb,
    0x0044bbbb,     0x0044bbbb,     0x0044bbbb,     0x0044bbbb,
    /* Four (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc0303,     0x0044bbbb,
    0x0044bbbb,     0x0044bbbb,     0x0044bbbb,     0x0044bbbb,
    /* Four (red) bottom-left */
    0x0048b7b7,     0x0048b7b7,     0x0050afaf,     0x00609f9f,
    0x0040bfbf,     0x007f8080,     0x0040bfbf,     0x0000ffff,
    /* Four (red) bottom-right */
    0x0044bbbb,     0x003cc3c3,     0x0004fbfb,     0x0004fbfb,
    0x0004fbfb,     0x00fc0303,     0x0004fbfb,     0x0000ffff,
    /* Four (green) top-left */
    0x0000ffff,     0x0000ffff,     0x007f80ff,     0x0044bbff,
    0x0044bbff,     0x0044bbff,     0x0044bbff,     0x0044bbff,
    /* Four (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc03ff,     0x0044bbff,
    0x0044bbff,     0x0044bbff,     0x0044bbff,     0x0044bbff,
    /* Four (green) bottom-left */
    0x0048b7ff,     0x0048b7ff,     0x0050afff,     0x00609fff,
    0x0040bfff,     0x007f80ff,     0x0040bfff,     0x0000ffff,
    /* Four (green) bottom-right */
    0x0044bbff,     0x003cc3ff,     0x0004fbff,     0x0004fbff,
    0x0004fbff,     0x00fc03ff,     0x0004fbff,     0x0000ffff,

    /* Five (black) top-left */
    0x0000ffff,     0x0000ff80,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000ffc0,     0x0000fffb,
    /* Five (black) top-right */
    0x0000ffff,     0x0000ff03,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ff0f,     0x0000ffef,
    /* Five (black) bottom-left */
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fff7,
    0x0000fff7,     0x0000fff7,     0x0000ff00,     0x0000ffff,
    /* Five (black) bottom-right */
    0x0000ffef,     0x0000ffef,     0x0000ffef,     0x0000ffef,
    0x0000ffef,     0x0000ffef,     0x0000ff01,     0x0000ffff,
    /* Five (red) top-left */
    0x0000ffff,     0x007f8080,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x003fc0c0,     0x0004fbfb,
    /* Five (red) top-right */
    0x0000ffff,     0x00fc0303,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x00f00f0f,     0x0010efef,
    /* Five (red) bottom-left */
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0008f7f7,
    0x0008f7f7,     0x0008f7f7,     0x00ff0000,     0x0000ffff,
    /* Five (red) bottom-right */
    0x0010efef,     0x0010efef,     0x0010efef,     0x0010efef,
    0x0010efef,     0x0010efef,     0x00fe0101,     0x0000ffff,
    /* Five (green) top-left */
    0x0000ffff,     0x007f80ff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x003fc0ff,     0x0004fbff,
    /* Five (green) top-right */
    0x0000ffff,     0x00fc03ff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x00f00fff,     0x0010efff,
    /* Five (green) bottom-left */
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0008f7ff,
    0x0008f7ff,     0x0008f7ff,     0x00ff00ff,     0x0000ffff,
    /* Five (green) bottom-right */
    0x0010efff,     0x0010efff,     0x0010efff,     0x0010efff,
    0x0010efff,     0x0010efff,     0x00fe01ff,     0x0000ffff,

    /* Six (black) top-left */
    0x0000fffd,     0x0000fffe,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff00,     0x0000ffff,     0x0000ffff,
    /* Six (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff7f,     0x0000ff7f,
    0x0000ffff,     0x0000ff01,     0x0000ffff,     0x0000ffff,
    /* Six (black) bottom-left */
    0x0000fffb,     0x0000fffb,     0x0000fff7,     0x0000fff7,
    0x0000ffef,     0x0000ffdf,     0x0000ffbf,     0x0000ffff,
    /* Six (black) bottom-right */
    0x0000ffbf,     0x0000ffdf,     0x0000ffef,     0x0000fff7,
    0x0000fff7,     0x0000fffb,     0x0000fffb,     0x0000ffff,
    /* Six (red) top-left */
    0x0002fdfd,     0x0001fefe,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff0000,     0x0000ffff,     0x0000ffff,
    /* Six (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00807f7f,     0x00807f7f,
    0x0000ffff,     0x00fe0101,     0x0000ffff,     0x0000ffff,
    /* Six (red) bottom-left */
    0x0004fbfb,     0x0004fbfb,     0x0008f7f7,     0x0008f7f7,
    0x0010efef,     0x0020dfdf,     0x0040bfbf,     0x0000ffff,
    /* Six (red) bottom-right */
    0x0040bfbf,     0x0020dfdf,     0x0010efef,     0x0008f7f7,
    0x0008f7f7,     0x0004fbfb,     0x0004fbfb,     0x0000ffff,
    /* Six (green) top-left */
    0x0002fdff,     0x0001feff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff00ff,     0x0000ffff,     0x0000ffff,
    /* Six (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00807fff,     0x00807fff,
    0x0000ffff,     0x00fe01ff,     0x0000ffff,     0x0000ffff,
    /* Six (green) bottom-left */
    0x0004fbff,     0x0004fbff,     0x0008f7ff,     0x0008f7ff,
    0x0010efff,     0x0020dfff,     0x0040bfff,     0x0000ffff,
    /* Six (green) bottom-right */
    0x0040bfff,     0x0020dfff,     0x0010efff,     0x0008f7ff,
    0x0008f7ff,     0x0004fbff,     0x0004fbff,     0x0000ffff,

    /* Seven (black) top-left */
    0x0000fffd,     0x0000fffd,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000fff8,     0x0000ff05,
    /* Seven (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffc3,     0x0000ff3f,     0x0000ffff,
    /* Seven (black) bottom-left */
    0x0000fffd,     0x0000fffd,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000fffe,     0x0000ffff,
    /* Seven (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000fffb,
    0x0000fffb,     0x0000fffb,     0x0000ff03,     0x0000ffff,
    /* Seven (red) top-left */
    0x0002fdfd,     0x0002fdfd,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x0007f8f8,     0x00fa0505,
    /* Seven (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x003cc3c3,     0x00c03f3f,     0x0000ffff,
    /* Seven (red) bottom-left */
    0x0002fdfd,     0x0002fdfd,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x0001fefe,     0x0000ffff,
    /* Seven (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0004fbfb,
    0x0004fbfb,     0x0004fbfb,     0x00fc0303,     0x0000ffff,
    /* Seven (green) top-left */
    0x0002fdff,     0x0002fdff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x0007f8ff,     0x00fa05ff,
    /* Seven (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x003cc3ff,     0x00c03fff,     0x0000ffff,
    /* Seven (green) bottom-left */
    0x0002fdff,     0x0002fdff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x0001feff,     0x0000ffff,
    /* Seven (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0004fbff,
    0x0004fbff,     0x0004fbff,     0x00fc03ff,     0x0000ffff,

    /* Eight (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000fffb,     0x0000fffb,
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    /* Eight (black) top-right */
    0x0000ffff,     0x0000ffbf,     0x0000ffbf,     0x0000ffbf,
    0x0000ffbf,     0x0000ffbf,     0x0000ffbf,     0x0000ffdf,
    /* Eight (black) bottom-left */
    0x0000fff7,     0x0000fff7,     0x0000fff7,     0x0000ffef,
    0x0000ffef,     0x0000ffdf,     0x0000ffdf,     0x0000ffbf,
    /* Eight (black) bottom-right */
    0x0000ffdf,     0x0000ffdf,     0x0000ffef,     0x0000ffef,
    0x0000fff7,     0x0000fff7,     0x0000fffb,     0x0000fffd,
    /* Eight (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0004fbfb,     0x0004fbfb,
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    /* Eight (red) top-right */
    0x0000ffff,     0x0040bfbf,     0x0040bfbf,     0x0040bfbf,
    0x0040bfbf,     0x0040bfbf,     0x0040bfbf,     0x0020dfdf,
    /* Eight (red) bottom-left */
    0x0008f7f7,     0x0008f7f7,     0x0008f7f7,     0x0010efef,
    0x0010efef,     0x0020dfdf,     0x0020dfdf,     0x0040bfbf,
    /* Eight (red) bottom-right */
    0x0020dfdf,     0x0020dfdf,     0x0010efef,     0x0010efef,
    0x0008f7f7,     0x0008f7f7,     0x0004fbfb,     0x0002fdfd,
    /* Eight (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0004fbff,     0x0004fbff,
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    /* Eight (green) top-right */
    0x0000ffff,     0x0040bfff,     0x0040bfff,     0x0040bfff,
    0x0040bfff,     0x0040bfff,     0x0040bfff,     0x0020dfff,
    /* Eight (green) bottom-left */
    0x0008f7ff,     0x0008f7ff,     0x0008f7ff,     0x0010efff,
    0x0010efff,     0x0020dfff,     0x0020dfff,     0x0040bfff,
    /* Eight (green) bottom-right */
    0x0020dfff,     0x0020dfff,     0x0010efff,     0x0010efff,
    0x0008f7ff,     0x0008f7ff,     0x0004fbff,     0x0002fdff,

    /* Nine (black) top-left */
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    0x0000ff80,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    /* Nine (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff1f,     0x0000ffdf,     0x0000ffdf,     0x0000ffdf,
    /* Nine (black) bottom-left */
    0x0000fff7,     0x0000fff7,     0x0000fff7,     0x0000ffef,
    0x0000ffef,     0x0000ffdf,     0x0000ffbf,     0x0000ff7f,
    /* Nine (black) bottom-right */
    0x0000ffdf,     0x0000ffdf,     0x0000ffdf,     0x0000ffdd,
    0x0000ffdd,     0x0000ffdd,     0x0000ffe1,     0x0000ffff,
    /* Nine (red) top-left */
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    0x007f8080,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    /* Nine (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00e01f1f,     0x0020dfdf,     0x0020dfdf,     0x0020dfdf,
    /* Nine (red) bottom-left */
    0x0008f7f7,     0x0008f7f7,     0x0008f7f7,     0x0010efef,
    0x0010efef,     0x0020dfdf,     0x0040bfbf,     0x00807f7f,
    /* Nine (red) bottom-right */
    0x0020dfdf,     0x0020dfdf,     0x0020dfdf,     0x0022dddd,
    0x0022dddd,     0x0022dddd,     0x001ee1e1,     0x0000ffff,
    /* Nine (green) top-left */
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    0x007f80ff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    /* Nine (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00e01fff,     0x0020dfff,     0x0020dfff,     0x0020dfff,
    /* Nine (green) bottom-left */
    0x0008f7ff,     0x0008f7ff,     0x0008f7ff,     0x0010efff,
    0x0010efff,     0x0020dfff,     0x0040bfff,     0x00807fff,
    /* Nine (green) bottom-right */
    0x0020dfff,     0x0020dfff,     0x0020dfff,     0x0022ddff,
    0x0022ddff,     0x0022ddff,     0x001ee1ff,     0x0000ffff,

    /*
     * 198 - Artwork for prints.
     */

    /* Claw top-left */
    0x0000ffff,     0x0000fffe,     0x0000fffe,     0x0000fffe,
    0x0000fffe,     0x0000fffe,     0x0000ff7e,     0x0000ff3e,
    /* Claw top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff7f,     0x0000ff7f,
    0x0000ff7f,     0x0000ff7f,     0x0000ff7e,     0x0000ff7c,
    /* Claw bottom-left */
    0x0000ff1e,     0x0000ff8e,     0x0000ffc6,     0x0000ffe2,
    0x0000fff0,     0x0000fff8,     0x0000fffc,     0x0000fffe,
    /* Claw bottom-right */
    0x0000ff78,     0x0000ff71,     0x0000ff63,     0x0000ff47,
    0x0000ff0f,     0x0000ff1f,     0x0000ff3f,     0x0000ff7f,

    /* Paw top-left */
    0x0000ffff,     0x000cf3f3,     0x001ee1e1,     0x001ee1e1,
    0x000cf3f3,     0x00609f9f,     0x00f00f0f,     0x00f00f0f,
    /* Paw top-right */
    0x0000ffff,     0x0030cfcf,     0x00788787,     0x00788787,
    0x0030cfcf,     0x0006f9f9,     0x000ff0f0,     0x000ff0f0,
    /* Paw bottom-left */
    0x00619e9e,     0x0007f8f8,     0x000ff0f0,     0x001fe0e0,
    0x003fc0c0,     0x003fc0c0,     0x001fe0e0,     0x0007f8f8,
    /* Paw bottom-right */
    0x00867979,     0x00e01f1f,     0x00f00f0f,     0x00f80707,
    0x00fc0303,     0x00fc0303,     0x00f80707,     0x00e01f1f,

    /* Hoof top-left */
    0x0002fdff,     0x0006f9ff,     0x0006f9ff,     0x000ef1ff,
    0x000cf3ff,     0x001ce3ff,     0x001ce3ff,     0x001ce3ff,
    /* Hoof top-right */
    0x0040bfff,     0x00609fff,     0x00609fff,     0x00708fff,
    0x0030cfff,     0x0038c7ff,     0x0038c7ff,     0x0038c7ff,
    /* Hoof bottom-left */
    0x001ee1ff,     0x001ee1ff,     0x000ef1ff,     0x0006f9ff,
    0x0000ffff,     0x0000ffff,     0x0006f9ff,     0x0006f9ff,
    /* Hoof bottom-right */
    0x007887ff,     0x007887ff,     0x00708fff,     0x00609fff,
    0x0000ffff,     0x0000ffff,     0x00609fff,     0x00609fff,

    /*
     * 210 - Snep artwork 4×4 (TODO).
     */

    /* Snep artwork (0, 0) */
    0x000f3f19,     0x000f3f19,     0x000f3f19,     0x000f3f19,
    0x000f3f19,     0x00073f1c,     0x00073f1c,     0x00033f1e,
    /* Snep artwork (1, 0) */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0080ffff,     0x0080ffff,     0x00c0ff7f,
    /* Snep artwork (2, 0) */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Snep artwork (3, 0) */
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    /* Snep artwork (0, 1) */
    0x00033f1e,     0x00013f1f,     0x00003f1f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Snep artwork (1, 1) */
    0x00e0ff3f,     0x00f0ff1f,     0x00f8ff8f,     0x007cffc7,
    0x003effe3,     0x001ffff1,     0x000ffff8,     0x0007fffc,
    /* Snep artwork (2, 1) */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0080ffff,     0x00c0ff7f,
    /* Snep artwork (3, 1) */
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    /* Snep artwork (0, 2) */
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Snep artwork (1, 2) */
    0x0003fffe,     0x0001ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Snep artwork (2, 2) */
    0x00e0ff3f,     0x00f0ff1f,     0x00f8ff8f,     0x007cffc7,
    0x003effe3,     0x001ffff1,     0x000ffff8,     0x0007fffc,
    /* Snep artwork (3, 2) */
    0x0000fcf8,     0x0000fcf8,     0x0000fcf8,     0x0000fcf8,
    0x0000fcf8,     0x0000fcf8,     0x0080fcf8,     0x00c0fc78,
    /* Snep artwork (0, 3) */
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    0x00003f1f,     0x00003f1f,     0x00003f1f,     0x00003f1f,
    /* Snep artwork (1, 3) */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Snep artwork (2, 3) */
    0x0003fffe,     0x0001ffff,     0x0001ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* Snep artwork (3, 3) */
    0x00c0fc78,     0x00e0fc38,     0x00e0fc38,     0x00f0fc98,
    0x00f0fc98,     0x00f0fc98,     0x00f0fc98,     0x00f0fc98,

    /*
     * 226 - Empty card outline.
     */

    /* Outline top-left */
    0x00000007,     0x00000008,     0x00000010,     0x00000020,
    0x00000020,     0x00000020,     0x00000020,     0x00000020,
    /* Outline top-edge */
    0x000000ff,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    /* Outline top-right */
    0x000000e0,     0x00000010,     0x00000008,     0x00000004,
    0x00000004,     0x00000004,     0x00000004,     0x00000004,
    /* Outline left-edge */
    0x00000020,     0x00000020,     0x00000020,     0x00000020,
    0x00000020,     0x00000020,     0x00000020,     0x00000020,
    /* Outline right-edge */
    0x00000004,     0x00000004,     0x00000004,     0x00000004,
    0x00000004,     0x00000004,     0x00000004,     0x00000004,
    /* Outline bottom-left */
    0x00000020,     0x00000020,     0x00000020,     0x00000020,
    0x00000020,     0x00000010,     0x00000008,     0x00000007,
    /* Outline bottom-edge */
    0x00000000,     0x00000000,     0x00000000,     0x00000000,
    0x00000000,     0x00000000,     0x00000000,     0x000000ff,
    /* Outline bottom-right */
    0x00000004,     0x00000004,     0x00000004,     0x00000004,
    0x00000004,     0x00000008,     0x00000010,     0x000000e0,

    /*
     * 234 - Buttons.
     */

    /* Claw button top-left (inactive) */
    0x00000000,     0x00000003,     0x0000000c,     0x00000110,
    0x00000120,     0x00000120,     0x00001140,     0x00001940,
    /* Claw button top-right (inactive) */
    0x00000000,     0x000000c0,     0x00000030,     0x00000008,
    0x00008004,     0x00008004,     0x00008802,     0x00009802,
    /* Claw button bottom-left (inactive) */
    0x00001d40,     0x00000f40,     0x00000720,     0x00000320,
    0x00000110,     0x0000000c,     0x00000003,     0x00000000,
    /* Claw button bottom-right (inactive) */
    0x0000b802,     0x0000f002,     0x0000e004,     0x0000c004,
    0x00008008,     0x00000030,     0x000000c0,     0x00000000,
    /* Claw button top-left (active) */
    0x00000000,     0x00000300,     0x00000c03,     0x0000110e,
    0x0000211e,     0x0000211e,     0x0000512e,     0x00005926,
    /* Claw button top-right (active) */
    0x00000000,     0x0000c000,     0x000030c0,     0x000008f0,
    0x00008478,     0x00008478,     0x00008a74,     0x00009a64,
    /* Claw button bottom-left (active) */
    0x00005d22,     0x00004f30,     0x00002718,     0x0000231c,
    0x0000110e,     0x00000c03,     0x00000300,     0x00000000,
    /* Claw button bottom-right (active) */
    0x0000ba44,     0x0000f20c,     0x0000e418,     0x0000c438,
    0x00008870,     0x000030c0,     0x0000c000,     0x00000000,

    /* Paw button top-left (inactive) */
    0x00000000,     0x00000003,     0x0000000c,     0x00000010,
    0x00060020,     0x00060020,     0x00000040,     0x00180040,
    /* Paw button top-right (inactive) */
    0x00000000,     0x000000c0,     0x00000030,     0x00000008,
    0x00600004,     0x00600004,     0x00000002,     0x00180002,
    /* Paw button bottom-left (inactive) */
    0x00190040,     0x00030040,     0x00070020,     0x00030020,
    0x00000010,     0x0000000c,     0x00000003,     0x00000000,
    /* Paw button bottom-right (inactive) */
    0x00980002,     0x00c00002,     0x00e00004,     0x00c00004,
    0x00000008,     0x00000030,     0x000000c0,     0x00000000,
    /* Paw button top-left (active) */
    0x00000000,     0x00000300,     0x00000c03,     0x0000100f,
    0x00062019,     0x00062019,     0x0000403f,     0x00184027,
    /* Paw button top-right (active) */
    0x00000000,     0x0000c000,     0x000030c0,     0x000008f0,
    0x00600498,     0x00600498,     0x000002fc,     0x001802e4,
    /* Paw button bottom-left (active) */
    0x00194026,     0x0003403c,     0x00072018,     0x0003201c,
    0x0000100f,     0x00000c03,     0x00000300,     0x00000000,
    /* Paw button bottom-right (active) */
    0x00980264,     0x00c0023c,     0x00e00418,     0x00c00438,
    0x000008f0,     0x000030c0,     0x0000c000,     0x00000000,

    /* Hoof button top-left (inactive) */
    0x00000000,     0x00000003,     0x0000000c,     0x00020012,
    0x00060026,     0x00060026,     0x000c004c,     0x000c004c,
    /* Hoof button top-right (inactive) */
    0x00000000,     0x000000c0,     0x00000030,     0x00400048,
    0x00600064,     0x00600064,     0x00300032,     0x00300032,
    /* Hoof button bottom-left (inactive) */
    0x000e004e,     0x000e004e,     0x00040024,     0x00000020,
    0x00020012,     0x0000000c,     0x00000003,     0x00000000,
    /* Hoof button bottom-right (inactive) */
    0x00700072,     0x00700072,     0x00200024,     0x00000004,
    0x00400048,     0x00000030,     0x000000c0,     0x00000000,
    /* Hoof button top-left (active) */
    0x00000000,     0x00000300,     0x00000c03,     0x0002100f,
    0x0006201f,     0x0006201f,     0x000c403f,     0x000c403f,
    /* Hoof button top-right (active) */
    0x00000000,     0x0000c000,     0x000030c0,     0x004008f0,
    0x006004f8,     0x006004f8,     0x003002fc,     0x003002fc,
    /* Hoof button bottom-left (active) */
    0x000e403f,     0x000e403f,     0x0004201f,     0x0000201f,
    0x0002100f,     0x00000c03,     0x00000300,     0x00000000,
    /* Hoof button bottom-right (active) */
    0x007002fc,     0x007002fc,     0x002004f8,     0x000004f8,
    0x004008f0,     0x000030c0,     0x0000c000,     0x00000000,

};

