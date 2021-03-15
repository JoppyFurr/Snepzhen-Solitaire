
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

    /*
     * Chinese characters are Gnu Unifont at 16 × 16 pixels.
     */

    /* 20 - One (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff00,
    /* 21 - One (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff01,
    /* 22 - One (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 23 - One (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 24 - One (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00ff0000,
    /* 25 - One (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00fe0101,
    /* 26 - One (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 27 - One (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 28 - One (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00ff00ff,
    /* 29 - One (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00fe01ff,
    /* 30 - One (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 31 - One (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,

    /* 32 - Two (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffc0,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 33 - Two (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff07,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 34 - Two (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff00,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 35 - Two (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff01,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 36 - Two (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0c0,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 37 - Two (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f80707,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 38 - Two (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00ff0000,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 39 - Two (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00fe0101,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 40 - Two (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0ff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 41 - Two (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f807ff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 42 - Two (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00ff00ff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    /* 43 - Two (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00fe01ff,     0x0000ffff,     0x0000ffff,     0x0000ffff,

    /* 44 - Three (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ff80,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffc0,
    /* 45 - Three (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff03,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ff07,
    /* 46 - Three (black) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff00,     0x0000ffff,     0x0000ffff,
    /* 47 - Three (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff01,     0x0000ffff,     0x0000ffff,
    /* 48 - Three (red) top-left */
    0x0000ffff,     0x0000ffff,     0x007f8080,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0c0,
    /* 49 - Three (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc0303,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f80707,
    /* 50 - Three (red) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff0000,     0x0000ffff,     0x0000ffff,
    /* 51 - Three (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00fe0101,     0x0000ffff,     0x0000ffff,
    /* 52 - Three (green) top-left */
    0x0000ffff,     0x0000ffff,     0x007f80ff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x003fc0ff,
    /* 53 - Three (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc03ff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x00f807ff,
    /* 54 - Three (green) bottom-left */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff00ff,     0x0000ffff,     0x0000ffff,
    /* 55 - Three (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00fe01ff,     0x0000ffff,     0x0000ffff,

    /* 56 - Four (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000ff80,     0x0000ffbb,
    0x0000ffbb,     0x0000ffbb,     0x0000ffbb,     0x0000ffbb,
    /* 57 - Four (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff03,     0x0000ffbb,
    0x0000ffbb,     0x0000ffbb,     0x0000ffbb,     0x0000ffbb,
    /* 58 - Four (black) bottom-left */
    0x0000ffb7,     0x0000ffb7,     0x0000ffaf,     0x0000ff9f,
    0x0000ffbf,     0x0000ff80,     0x0000ffbf,     0x0000ffff,
    /* 59 - Four (black) bottom-right */
    0x0000ffbb,     0x0000ffc3,     0x0000fffb,     0x0000fffb,
    0x0000fffb,     0x0000ff03,     0x0000fffb,     0x0000ffff,
    /* 60 - Four (red) top-left */
    0x0000ffff,     0x0000ffff,     0x007f8080,     0x0044bbbb,
    0x0044bbbb,     0x0044bbbb,     0x0044bbbb,     0x0044bbbb,
    /* 61 - Four (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc0303,     0x0044bbbb,
    0x0044bbbb,     0x0044bbbb,     0x0044bbbb,     0x0044bbbb,
    /* 62 - Four (red) bottom-left */
    0x0048b7b7,     0x0048b7b7,     0x0050afaf,     0x00609f9f,
    0x0040bfbf,     0x007f8080,     0x0040bfbf,     0x0000ffff,
    /* 63 - Four (red) bottom-right */
    0x0044bbbb,     0x003cc3c3,     0x0004fbfb,     0x0004fbfb,
    0x0004fbfb,     0x00fc0303,     0x0004fbfb,     0x0000ffff,
    /* 64 - Four (green) top-left */
    0x0000ffff,     0x0000ffff,     0x007f80ff,     0x0044bbff,
    0x0044bbff,     0x0044bbff,     0x0044bbff,     0x0044bbff,
    /* 65 - Four (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00fc03ff,     0x0044bbff,
    0x0044bbff,     0x0044bbff,     0x0044bbff,     0x0044bbff,
    /* 66 - Four (green) bottom-left */
    0x0048b7ff,     0x0048b7ff,     0x0050afff,     0x00609fff,
    0x0040bfff,     0x007f80ff,     0x0040bfff,     0x0000ffff,
    /* 67 - Four (green) bottom-right */
    0x0044bbff,     0x003cc3ff,     0x0004fbff,     0x0004fbff,
    0x0004fbff,     0x00fc03ff,     0x0004fbff,     0x0000ffff,

    /* 68 - Five (black) top-left */
    0x0000ffff,     0x0000ff80,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000ffc0,     0x0000fffb,
    /* 69 - Five (black) top-right */
    0x0000ffff,     0x0000ff03,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x0000ff0f,     0x0000ffef,
    /* 70 - Five (black) bottom-left */
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fff7,
    0x0000fff7,     0x0000fff7,     0x0000ff00,     0x0000ffff,
    /* 71 - Five (black) bottom-right */
    0x0000ffef,     0x0000ffef,     0x0000ffef,     0x0000ffef,
    0x0000ffef,     0x0000ffef,     0x0000ff01,     0x0000ffff,
    /* 72 - Five (red) top-left */
    0x0000ffff,     0x007f8080,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x003fc0c0,     0x0004fbfb,
    /* 73 - Five (red) top-right */
    0x0000ffff,     0x00fc0303,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x00f00f0f,     0x0010efef,
    /* 74 - Five (red) bottom-left */
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0008f7f7,
    0x0008f7f7,     0x0008f7f7,     0x00ff0000,     0x0000ffff,
    /* 75 - Five (red) bottom-right */
    0x0010efef,     0x0010efef,     0x0010efef,     0x0010efef,
    0x0010efef,     0x0010efef,     0x00fe0101,     0x0000ffff,
    /* 76 - Five (green) top-left */
    0x0000ffff,     0x007f80ff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x003fc0ff,     0x0004fbff,
    /* 77 - Five (green) top-right */
    0x0000ffff,     0x00fc03ff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffff,     0x00f00fff,     0x0010efff,
    /* 78 - Five (green) bottom-left */
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0008f7ff,
    0x0008f7ff,     0x0008f7ff,     0x00ff00ff,     0x0000ffff,
    /* 79 - Five (green) bottom-right */
    0x0010efff,     0x0010efff,     0x0010efff,     0x0010efff,
    0x0010efff,     0x0010efff,     0x00fe01ff,     0x0000ffff,

    /* 80 - Six (black) top-left */
    0x0000fffd,     0x0000fffe,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ff00,     0x0000ffff,     0x0000ffff,
    /* 81 - Six (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ff7f,     0x0000ff7f,
    0x0000ffff,     0x0000ff01,     0x0000ffff,     0x0000ffff,
    /* 82 - Six (black) bottom-left */
    0x0000fffb,     0x0000fffb,     0x0000fff7,     0x0000fff7,
    0x0000ffef,     0x0000ffdf,     0x0000ffbf,     0x0000ffff,
    /* 83 - Six (black) bottom-right */
    0x0000ffbf,     0x0000ffdf,     0x0000ffef,     0x0000fff7,
    0x0000fff7,     0x0000fffb,     0x0000fffb,     0x0000ffff,
    /* 84 - Six (red) top-left */
    0x0002fdfd,     0x0001fefe,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff0000,     0x0000ffff,     0x0000ffff,
    /* 85 - Six (red) top-right */
    0x0000ffff,     0x0000ffff,     0x00807f7f,     0x00807f7f,
    0x0000ffff,     0x00fe0101,     0x0000ffff,     0x0000ffff,
    /* 86 - Six (red) bottom-left */
    0x0004fbfb,     0x0004fbfb,     0x0008f7f7,     0x0008f7f7,
    0x0010efef,     0x0020dfdf,     0x0040bfbf,     0x0000ffff,
    /* 87 - Six (red) bottom-right */
    0x0040bfbf,     0x0020dfdf,     0x0010efef,     0x0008f7f7,
    0x0008f7f7,     0x0004fbfb,     0x0004fbfb,     0x0000ffff,
    /* 88 - Six (green) top-left */
    0x0002fdff,     0x0001feff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x00ff00ff,     0x0000ffff,     0x0000ffff,
    /* 89 - Six (green) top-right */
    0x0000ffff,     0x0000ffff,     0x00807fff,     0x00807fff,
    0x0000ffff,     0x00fe01ff,     0x0000ffff,     0x0000ffff,
    /* 90 - Six (green) bottom-left */
    0x0004fbff,     0x0004fbff,     0x0008f7ff,     0x0008f7ff,
    0x0010efff,     0x0020dfff,     0x0040bfff,     0x0000ffff,
    /* 91 - Six (green) bottom-right */
    0x0040bfff,     0x0020dfff,     0x0010efff,     0x0008f7ff,
    0x0008f7ff,     0x0004fbff,     0x0004fbff,     0x0000ffff,

    /* 92 - Seven (black) top-left */
    0x0000fffd,     0x0000fffd,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000fff8,     0x0000ff05,
    /* 93 - Seven (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x0000ffc3,     0x0000ff3f,     0x0000ffff,
    /* 94 - Seven (black) bottom-left */
    0x0000fffd,     0x0000fffd,     0x0000fffd,     0x0000fffd,
    0x0000fffd,     0x0000fffd,     0x0000fffe,     0x0000ffff,
    /* 95 - Seven (black) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000fffb,
    0x0000fffb,     0x0000fffb,     0x0000ff03,     0x0000ffff,
    /* 96 - Seven (red) top-left */
    0x0002fdfd,     0x0002fdfd,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x0007f8f8,     0x00fa0505,
    /* 97 - Seven (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x003cc3c3,     0x00c03f3f,     0x0000ffff,
    /* 98 - Seven (red) bottom-left */
    0x0002fdfd,     0x0002fdfd,     0x0002fdfd,     0x0002fdfd,
    0x0002fdfd,     0x0002fdfd,     0x0001fefe,     0x0000ffff,
    /* 99 - Seven (red) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0004fbfb,
    0x0004fbfb,     0x0004fbfb,     0x00fc0303,     0x0000ffff,
    /* 100 - Seven (green) top-left */
    0x0002fdff,     0x0002fdff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x0007f8ff,     0x00fa05ff,
    /* 101 - Seven (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ffff,     0x003cc3ff,     0x00c03fff,     0x0000ffff,
    /* 102 - Seven (green) bottom-left */
    0x0002fdff,     0x0002fdff,     0x0002fdff,     0x0002fdff,
    0x0002fdff,     0x0002fdff,     0x0001feff,     0x0000ffff,
    /* 103 - Seven (green) bottom-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0004fbff,
    0x0004fbff,     0x0004fbff,     0x00fc03ff,     0x0000ffff,

    /* 104 - Eight (black) top-left */
    0x0000ffff,     0x0000ffff,     0x0000fffb,     0x0000fffb,
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    /* 105 - Eight (black) top-right */
    0x0000ffff,     0x0000ffbf,     0x0000ffbf,     0x0000ffbf,
    0x0000ffbf,     0x0000ffbf,     0x0000ffbf,     0x0000ffdf,
    /* 106 - Eight (black) bottom-left */
    0x0000fff7,     0x0000fff7,     0x0000fff7,     0x0000ffef,
    0x0000ffef,     0x0000ffdf,     0x0000ffdf,     0x0000ffbf,
    /* 107 - Eight (black) bottom-right */
    0x0000ffdf,     0x0000ffdf,     0x0000ffef,     0x0000ffef,
    0x0000fff7,     0x0000fff7,     0x0000fffb,     0x0000fffd,
    /* 108 - Eight (red) top-left */
    0x0000ffff,     0x0000ffff,     0x0004fbfb,     0x0004fbfb,
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    /* 109 - Eight (red) top-right */
    0x0000ffff,     0x0040bfbf,     0x0040bfbf,     0x0040bfbf,
    0x0040bfbf,     0x0040bfbf,     0x0040bfbf,     0x0020dfdf,
    /* 110 - Eight (red) bottom-left */
    0x0008f7f7,     0x0008f7f7,     0x0008f7f7,     0x0010efef,
    0x0010efef,     0x0020dfdf,     0x0020dfdf,     0x0040bfbf,
    /* 111 - Eight (red) bottom-right */
    0x0020dfdf,     0x0020dfdf,     0x0010efef,     0x0010efef,
    0x0008f7f7,     0x0008f7f7,     0x0004fbfb,     0x0002fdfd,
    /* 112 - Eight (green) top-left */
    0x0000ffff,     0x0000ffff,     0x0004fbff,     0x0004fbff,
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    /* 113 - Eight (green) top-right */
    0x0000ffff,     0x0040bfff,     0x0040bfff,     0x0040bfff,
    0x0040bfff,     0x0040bfff,     0x0040bfff,     0x0020dfff,
    /* 114 - Eight (green) bottom-left */
    0x0008f7ff,     0x0008f7ff,     0x0008f7ff,     0x0010efff,
    0x0010efff,     0x0020dfff,     0x0020dfff,     0x0040bfff,
    /* 115 - Eight (green) bottom-right */
    0x0020dfff,     0x0020dfff,     0x0010efff,     0x0010efff,
    0x0008f7ff,     0x0008f7ff,     0x0004fbff,     0x0002fdff,

    /* 116 - Nine (black) top-left */
    0x0000fffb,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    0x0000ff80,     0x0000fffb,     0x0000fffb,     0x0000fffb,
    /* 117 - Nine (black) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x0000ff1f,     0x0000ffdf,     0x0000ffdf,     0x0000ffdf,
    /* 118 - Nine (black) bottom-left */
    0x0000fff7,     0x0000fff7,     0x0000fff7,     0x0000ffef,
    0x0000ffef,     0x0000ffdf,     0x0000ffbf,     0x0000ff7f,
    /* 119 - Nine (black) bottom-right */
    0x0000ffdf,     0x0000ffdf,     0x0000ffdf,     0x0000ffdd,
    0x0000ffdd,     0x0000ffdd,     0x0000ffe1,     0x0000ffff,
    /* 120 - Nine (red) top-left */
    0x0004fbfb,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    0x007f8080,     0x0004fbfb,     0x0004fbfb,     0x0004fbfb,
    /* 121 - Nine (red) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00e01f1f,     0x0020dfdf,     0x0020dfdf,     0x0020dfdf,
    /* 122 - Nine (red) bottom-left */
    0x0008f7f7,     0x0008f7f7,     0x0008f7f7,     0x0010efef,
    0x0010efef,     0x0020dfdf,     0x0040bfbf,     0x00807f7f,
    /* 123 - Nine (red) bottom-right */
    0x0020dfdf,     0x0020dfdf,     0x0020dfdf,     0x0022dddd,
    0x0022dddd,     0x0022dddd,     0x001ee1e1,     0x0000ffff,
    /* 124 - Nine (green) top-left */
    0x0004fbff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    0x007f80ff,     0x0004fbff,     0x0004fbff,     0x0004fbff,
    /* 125 - Nine (green) top-right */
    0x0000ffff,     0x0000ffff,     0x0000ffff,     0x0000ffff,
    0x00e01fff,     0x0020dfff,     0x0020dfff,     0x0020dfff,
    /* 126 - Nine (green) bottom-left */
    0x0008f7ff,     0x0008f7ff,     0x0008f7ff,     0x0010efff,
    0x0010efff,     0x0020dfff,     0x0040bfff,     0x00807fff,
    /* 127 - Nine (green) bottom-right */
    0x0020dfff,     0x0020dfff,     0x0020dfff,     0x0022ddff,
    0x0022ddff,     0x0022ddff,     0x001ee1ff,     0x0000ffff,
};

