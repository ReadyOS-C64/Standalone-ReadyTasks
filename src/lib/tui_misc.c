/*
 * ReadyTasks - Extracted from Ready OS - https://readyos.notion.site
 * (C) Karl Prosser 2026 - MIT License
 */

/*
 * tui_misc.c - Numeric formatting helper for ReadyTasks
 */

#include "tui.h"

void tui_print_uint(unsigned char x, unsigned char y, unsigned int value,
                    unsigned char color) {
    static char buf[6];
    unsigned char pos;

    pos = 5;
    buf[5] = 0;

    do {
        --pos;
        buf[pos] = '0' + (value % 10);
        value /= 10;
    } while (value > 0 && pos > 0);

    tui_puts(x, y, &buf[pos], color);
}
