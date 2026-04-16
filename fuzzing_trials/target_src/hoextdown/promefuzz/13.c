// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_buffer_init at buffer.c:48:1 in buffer.h
// hoedown_buffer_putc at buffer.c:138:1 in buffer.h
// hoedown_buffer_printf at buffer.c:238:1 in buffer.h
// hoedown_buffer_slurp at buffer.c:210:1 in buffer.h
// hoedown_buffer_reset at buffer.c:93:1 in buffer.h
// hoedown_buffer_uninit at buffer.c:66:1 in buffer.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buffer.h"

static void *custom_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

static void custom_free(void *ptr) {
    free(ptr);
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a hoedown_buffer
    hoedown_buffer buffer;
    hoedown_buffer_init(&buffer, 16, custom_realloc, custom_free, custom_free);

    // Use hoedown_buffer_putc
    hoedown_buffer_putc(&buffer, Data[0]);

    // Use hoedown_buffer_printf
    if (Size > 1) {
        char format[] = "%02x";
        hoedown_buffer_printf(&buffer, format, Data[1]);
    }

    // Use hoedown_buffer_slurp
    if (Size > 2) {
        size_t slurp_size = Data[2] % (buffer.size + 1); // Ensure slurp_size is within bounds
        hoedown_buffer_slurp(&buffer, slurp_size);
    }

    // Reset the buffer
    hoedown_buffer_reset(&buffer);

    // Uninitialize the buffer
    hoedown_buffer_uninit(&buffer);

    return 0;
}