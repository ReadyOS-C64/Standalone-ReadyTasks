/*
 * ReadyTasks - Extracted from Ready OS - https://readyos.notion.site
 * (C) Karl Prosser 2026 - MIT License
 */

/*
 * clipboard_local.h - Single-item local clipboard for ReadyTasks
 */

#ifndef CLIPBOARD_LOCAL_H
#define CLIPBOARD_LOCAL_H

/* Clear clipboard state */
void clip_local_clear(void);

/* Returns 1 when clipboard has data, else 0 */
unsigned char clip_local_has_item(void);

/* Copy data into local clipboard. Returns stored byte count. */
unsigned int clip_local_copy(const void *data, unsigned int size);

/* Paste from local clipboard into output buffer. Returns copied byte count. */
unsigned int clip_local_paste(void *out, unsigned int maxsize);

#endif /* CLIPBOARD_LOCAL_H */
