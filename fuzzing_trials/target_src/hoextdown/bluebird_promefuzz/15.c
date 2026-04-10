#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "/src/hoextdown/src/buffer.h"

static hoedown_buffer* create_buffer(size_t unit) {
    hoedown_buffer *buf = malloc(sizeof(hoedown_buffer));
    if (!buf) return NULL;
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
    buf->unit = unit;
    buf->data_realloc = realloc;
    buf->data_free = free;
    buf->buffer_free = free;
    return buf;
}

static void free_buffer(hoedown_buffer *buf) {
    if (buf) {
        if (buf->data_free && buf->data) {
            buf->data_free(buf->data);
        }
        if (buf->buffer_free) {
            buf->buffer_free(buf);
        }
    }
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    hoedown_buffer *buf = create_buffer(64);
    if (!buf) return 0;

    // Ensure the input is null-terminated for string operations
    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) {
        free_buffer(buf);
        return 0;
    }
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Test hoedown_buffer_puts
    hoedown_buffer_puts(buf, input_str);

    // Test hoedown_buffer_cstr
    const char *cstr = hoedown_buffer_cstr(buf);

    // Test hoedown_buffer_printf
    hoedown_buffer_printf(buf, "Formatted: %s", input_str);

    // Test hoedown_buffer_prefix
    int prefix_result = hoedown_buffer_prefix(buf, input_str);

    // Test hoedown_buffer_eqs
    int eqs_result = hoedown_buffer_eqs(buf, input_str);

    // Test hoedown_buffer_sets
    hoedown_buffer_sets(buf, input_str);

    // Cleanup
    free(input_str);
    free_buffer(buf);

    return 0;
}