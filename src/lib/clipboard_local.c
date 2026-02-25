/*
 * ReadyTasks - Extracted from Ready OS - https://readyos.notion.site
 * (C) Karl Prosser 2026 - MIT License
 */

/*
 * clipboard_local.c - Single-item local clipboard for ReadyTasks
 */

#include "clipboard_local.h"
#include <string.h>

#define CLIP_LOCAL_CAPACITY 512

static unsigned char clip_local_has_data;
static unsigned int clip_local_size;
static unsigned char clip_local_buf[CLIP_LOCAL_CAPACITY];

void clip_local_clear(void) {
    clip_local_has_data = 0;
    clip_local_size = 0;
}

unsigned char clip_local_has_item(void) {
    return clip_local_has_data;
}

unsigned int clip_local_copy(const void *data, unsigned int size) {
    unsigned int copy_size;

    if (data == 0 || size == 0) {
        clip_local_clear();
        return 0;
    }

    copy_size = (size > CLIP_LOCAL_CAPACITY) ? CLIP_LOCAL_CAPACITY : size;
    memcpy(clip_local_buf, data, copy_size);
    clip_local_size = copy_size;
    clip_local_has_data = 1;
    return copy_size;
}

unsigned int clip_local_paste(void *out, unsigned int maxsize) {
    unsigned int copy_size;

    if (!clip_local_has_data || out == 0 || maxsize == 0) {
        return 0;
    }

    copy_size = (clip_local_size > maxsize) ? maxsize : clip_local_size;
    memcpy(out, clip_local_buf, copy_size);
    return copy_size;
}
