/*
 * ReadyTasks - Extracted from Ready OS - https://readyos.notion.site
 * (C) Karl Prosser 2026 - MIT License
 */

/*
 * tui.h - Minimal TUI library for ReadyTasks
 */

#ifndef TUI_H
#define TUI_H

/* Screen dimensions */
#define TUI_SCREEN_WIDTH  40
#define TUI_SCREEN_HEIGHT 25

/* Screen memory */
#define TUI_SCREEN    ((unsigned char*)0x0400)
#define TUI_COLOR_RAM ((unsigned char*)0xD800)

/* PETSCII box drawing (screen codes) */
#define TUI_CORNER_TL   0x70
#define TUI_CORNER_TR   0x6E
#define TUI_CORNER_BL   0x6D
#define TUI_CORNER_BR   0x7D
#define TUI_HLINE       0x40
#define TUI_VLINE       0x5D
#define TUI_T_RIGHT     0x6B

/* Colors */
#define TUI_COLOR_BLACK       0
#define TUI_COLOR_WHITE       1
#define TUI_COLOR_RED         2
#define TUI_COLOR_CYAN        3
#define TUI_COLOR_PURPLE      4
#define TUI_COLOR_GREEN       5
#define TUI_COLOR_BLUE        6
#define TUI_COLOR_YELLOW      7
#define TUI_COLOR_ORANGE      8
#define TUI_COLOR_BROWN       9
#define TUI_COLOR_LIGHTRED   10
#define TUI_COLOR_GRAY1      11
#define TUI_COLOR_GRAY2      12
#define TUI_COLOR_LIGHTGREEN 13
#define TUI_COLOR_LIGHTBLUE  14
#define TUI_COLOR_GRAY3      15

/* Default standalone theme */
#define TUI_THEME_BG          TUI_COLOR_BLACK
#define TUI_THEME_FG          TUI_COLOR_WHITE
#define TUI_THEME_BORDER      TUI_COLOR_GRAY3
#define TUI_THEME_TITLE       TUI_COLOR_LIGHTGREEN
#define TUI_THEME_HIGHLIGHT   TUI_COLOR_CYAN
#define TUI_THEME_STATUS      TUI_COLOR_GRAY3

/* Key codes */
#define TUI_KEY_RETURN  13
#define TUI_KEY_UP      145
#define TUI_KEY_DOWN    17
#define TUI_KEY_LEFT    157
#define TUI_KEY_RIGHT   29
#define TUI_KEY_HOME    19
#define TUI_KEY_DEL     20
#define TUI_KEY_F1      133
#define TUI_KEY_F2      137
#define TUI_KEY_F3      134
#define TUI_KEY_F4      138
#define TUI_KEY_F5      135
#define TUI_KEY_F6      139
#define TUI_KEY_F7      136
#define TUI_KEY_F8      140
#define TUI_KEY_RUNSTOP 3
#define TUI_KEY_LARROW  95

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char w;
    unsigned char h;
} TuiRect;

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char width;
    unsigned char maxlen;
    unsigned char cursor;
    unsigned char color;
    char *buffer;
} TuiInput;

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char w;
    unsigned char h;
    unsigned char count;
    unsigned char selected;
    unsigned char scroll_offset;
    unsigned char item_color;
    unsigned char sel_color;
    const char **items;
} TuiMenu;

void tui_init(void);
void tui_clear(unsigned char bg_color);
void tui_putc(unsigned char x, unsigned char y, unsigned char ch, unsigned char color);
void tui_puts(unsigned char x, unsigned char y, const char *str, unsigned char color);
void tui_puts_n(unsigned char x, unsigned char y, const char *str,
                unsigned char maxlen, unsigned char color);
void tui_hline(unsigned char x, unsigned char y, unsigned char len, unsigned char color);
void tui_vline(unsigned char x, unsigned char y, unsigned char len, unsigned char color);
void tui_clear_line(unsigned char y, unsigned char x, unsigned char len, unsigned char color);
void tui_window(const TuiRect *rect, unsigned char border_color);
void tui_window_title(const TuiRect *rect, const char *title,
                      unsigned char border_color, unsigned char title_color);

void tui_menu_init(TuiMenu *menu, unsigned char x, unsigned char y,
                   unsigned char w, unsigned char h,
                   const char **items, unsigned char count);
void tui_menu_draw(TuiMenu *menu);
unsigned char tui_menu_input(TuiMenu *menu, unsigned char key);

void tui_input_init(TuiInput *input, unsigned char x, unsigned char y,
                    unsigned char width, unsigned char maxlen,
                    char *buffer, unsigned char color);
void tui_input_draw(TuiInput *input);
unsigned char tui_input_key(TuiInput *input, unsigned char key);

unsigned char tui_getkey(void);
unsigned char tui_ascii_to_screen(unsigned char ascii);
void tui_print_uint(unsigned char x, unsigned char y, unsigned int value,
                    unsigned char color);

#endif /* TUI_H */
