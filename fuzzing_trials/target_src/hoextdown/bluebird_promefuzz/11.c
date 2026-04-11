#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/hoextdown/src/buffer.h"

static void initialize_buffer(hoedown_buffer *buf) {
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
    buf->unit = 64; // Arbitrary non-zero positive value for unit
    buf->data_realloc = realloc;
    buf->data_free = free;
    buf->buffer_free = free;
}

static void cleanup_buffer(hoedown_buffer *buf) {
    if (buf->data) {
        buf->data_free(buf->data);
    }
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    hoedown_buffer buf;
    initialize_buffer(&buf);

    // Fuzz hoedown_buffer_putc
    if (Size > 0) {
        hoedown_buffer_putc(&buf, Data[0]);
    }

    // Fuzz hoedown_buffer_cstr
    const char *cstr = hoedown_buffer_cstr(&buf);

    // Fuzz hoedown_buffer_printf
    hoedown_buffer_printf(&buf, "Fuzzing with size %zu", Size);

    // Fuzz hoedown_buffer_reset
    hoedown_buffer_reset(&buf);

    // Fuzz hoedown_buffer_slurp
    if (Size > 0) {
        hoedown_buffer_slurp(&buf, Size / 2);
    }

    // Fuzz hoedown_buffer_putf
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);

        dummy_file = fopen("./dummy_file", "rb");
        if (dummy_file) {
            hoedown_buffer_putf(&buf, dummy_file);
            fclose(dummy_file);
        }
    }

    cleanup_buffer(&buf);
    return 0;
}