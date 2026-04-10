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

static void initialize_buffer(hoedown_buffer *buf) {
    buf->data = NULL;
    buf->size = 0;
    buf->asize = 0;
    buf->unit = 64; // Example unit size
    buf->data_realloc = realloc;
    buf->data_free = free;
    buf->buffer_free = NULL;
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    hoedown_buffer buf;
    initialize_buffer(&buf);

    // Fuzz hoedown_buffer_grow
    size_t grow_size = Size > 0 ? Data[0] : 1;
    hoedown_buffer_grow(&buf, grow_size);

    // Fuzz hoedown_buffer_puts
    char *str = (char *)malloc(Size + 1);
    if (str) {
        memcpy(str, Data, Size);
        str[Size] = '\0';
        hoedown_buffer_puts(&buf, str);
        free(str);
    }

    // Fuzz hoedown_escape_href
    hoedown_buffer ob;
    initialize_buffer(&ob);
    hoedown_escape_href(&ob, Data, Size);
    hoedown_buffer_free(&ob);

    // Fuzz hoedown_buffer_set
    hoedown_buffer_set(&buf, Data, Size);

    // Fuzz hoedown_buffer_put
    hoedown_buffer_put(&buf, Data, Size);

    // Cleanup
    hoedown_buffer_free(&buf);

    return 0;
}