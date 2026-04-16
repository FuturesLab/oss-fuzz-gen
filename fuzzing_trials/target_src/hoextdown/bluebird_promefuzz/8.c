#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"
#include "/src/hoextdown/src/escape.h"

static void initialize_buffer(hoedown_buffer *buf, size_t unit) {
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
    buf->unit = unit;
    buf->data_realloc = (hoedown_realloc_callback)realloc;
    buf->data_free = (hoedown_free_callback)free;
    buf->buffer_free = NULL;
}

static void cleanup_buffer(hoedown_buffer *buf) {
    if (buf->data) {
        buf->data_free(buf->data);
    }
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize buffers
    hoedown_buffer *buf1 = hoedown_buffer_new(16);
    hoedown_buffer *buf2 = hoedown_buffer_new(16);
    if (!buf1 || !buf2) return 0;

    // Test hoedown_buffer_grow
    hoedown_buffer_grow(buf1, Size);

    // Test hoedown_buffer_eq
    hoedown_buffer_eq(buf1, Data, Size);

    // Test hoedown_buffer_put_utf8
    if (Size >= 4) {
        unsigned int codepoint = *(unsigned int *)Data;
        hoedown_buffer_put_utf8(buf1, codepoint);
    }

    // Test hoedown_buffer_prefix
    const char *prefix = (const char *)Data;
    hoedown_buffer_prefix(buf1, prefix);

    // Test hoedown_escape_html
    hoedown_escape_html(buf2, Data, Size, 1);

    // Cleanup
    cleanup_buffer(buf1);
    cleanup_buffer(buf2);
    free(buf1);
    free(buf2);

    return 0;
}