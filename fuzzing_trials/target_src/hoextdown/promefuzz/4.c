// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_buffer_put at buffer.c:120:1 in buffer.h
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_html_renderer_new at html.c:1110:1 in html.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_document_new at document.c:3979:1 in document.h
// hoedown_html_renderer_free at html.c:1185:1 in html.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_document_render at document.c:4070:1 in document.h
// hoedown_document_free at document.c:4246:1 in document.h
// hoedown_html_renderer_free at html.c:1185:1 in html.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "buffer.h"
#include "html.h"
#include "document.h"

static void fuzz_hoedown_buffer_put(hoedown_buffer *buffer, const uint8_t *data, size_t size) {
    if (buffer && data && size > 0) {
        hoedown_buffer_put(buffer, data, size);
    }
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create initial buffers
    size_t unit_size = 64;
    hoedown_buffer *buffer1 = hoedown_buffer_new(unit_size);
    hoedown_buffer *buffer2 = hoedown_buffer_new(unit_size);
    hoedown_buffer *buffer3 = hoedown_buffer_new(unit_size);

    if (!buffer1 || !buffer2 || !buffer3) {
        if (buffer1) hoedown_buffer_free(buffer1);
        if (buffer2) hoedown_buffer_free(buffer2);
        if (buffer3) hoedown_buffer_free(buffer3);
        return 0;
    }

    // Append data to buffer1
    fuzz_hoedown_buffer_put(buffer1, Data, Size);

    // Create HTML renderer
    hoedown_renderer *renderer = hoedown_html_renderer_new(HOEDOWN_HTML_USE_XHTML, 1);
    if (!renderer) {
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
        hoedown_buffer_free(buffer3);
        return 0;
    }

    // Create document
    hoedown_document *document = hoedown_document_new(renderer, HOEDOWN_EXT_AUTOLINK, 1, 0, NULL, buffer2);
    if (!document) {
        hoedown_html_renderer_free(renderer);
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
        hoedown_buffer_free(buffer3);
        return 0;
    }

    // Render document
    hoedown_document_render(document, buffer3, Data, Size);

    // Free resources
    hoedown_document_free(document);
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(buffer1);
    hoedown_buffer_free(buffer2);
    hoedown_buffer_free(buffer3);

    return 0;
}