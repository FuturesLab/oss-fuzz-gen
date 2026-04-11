// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_document_new at document.c:3979:1 in document.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_document_render_inline at document.c:4186:1 in document.h
// hoedown_document_free at document.c:4246:1 in document.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "document.h"

static hoedown_renderer mock_renderer;
static hoedown_renderer_data mock_renderer_data;
static hoedown_user_block mock_user_block;

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Step 1: Allocate buffers
    size_t unit_size = Size > 0 ? Size : 1;
    hoedown_buffer *buffer1 = hoedown_buffer_new(unit_size);
    hoedown_buffer *buffer2 = hoedown_buffer_new(unit_size);

    if (!buffer1 || !buffer2) {
        if (buffer1) hoedown_buffer_free(buffer1);
        if (buffer2) hoedown_buffer_free(buffer2);
        return 0;
    }

    // Step 2: Create a document
    size_t max_nesting = Size > 0 ? Size : 1;
    hoedown_document *document = hoedown_document_new(
        &mock_renderer, HOEDOWN_EXT_AUTOLINK, max_nesting, 1, mock_user_block, buffer1);

    if (!document) {
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
        return 0;
    }

    // Step 3: Render inline Markdown
    hoedown_document_render_inline(document, buffer2, Data, Size);

    // Step 4: Clean up
    hoedown_document_free(document);
    hoedown_buffer_free(buffer1);
    hoedown_buffer_free(buffer2);

    return 0;
}