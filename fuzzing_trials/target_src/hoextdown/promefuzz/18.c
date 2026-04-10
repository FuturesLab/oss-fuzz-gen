// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_document_new at document.c:3979:1 in document.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_document_render at document.c:4070:1 in document.h
// hoedown_document_render_inline at document.c:4186:1 in document.h
// hoedown_buffer_put at buffer.c:120:1 in buffer.h
// hoedown_document_free at document.c:4246:1 in document.h
// hoedown_buffer_free at buffer.c:81:1 in buffer.h
// hoedown_buffer_new at buffer.c:73:1 in buffer.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "document.h"

static hoedown_buffer *create_buffer(size_t unit) {
    hoedown_buffer *buf = hoedown_buffer_new(unit);
    if (buf && unit > 0) {
        buf->data_realloc = realloc;
        buf->data_free = free;
    }
    return buf;
}

static hoedown_document *create_document() {
    hoedown_renderer renderer = {0};
    hoedown_buffer *meta = create_buffer(64);
    hoedown_document *doc = hoedown_document_new(&renderer, 0, 16, 0, NULL, meta);
    hoedown_buffer_free(meta); // Free meta buffer after creating document
    return doc;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    hoedown_buffer *ob = create_buffer(64);
    if (!ob) return 0;

    hoedown_document *doc = create_document();
    if (!doc) {
        hoedown_buffer_free(ob);
        return 0;
    }

    // Ensure the input data is not null and the buffer is properly initialized
    if (Data && Size > 0 && ob->data && ob->asize >= Size) {
        // Fuzz hoedown_document_render
        hoedown_document_render(doc, ob, Data, Size);

        // Fuzz hoedown_document_render_inline
        hoedown_document_render_inline(doc, ob, Data, Size);

        // Fuzz hoedown_buffer_put
        hoedown_buffer_put(ob, Data, Size);
    }

    // Cleanup
    hoedown_document_free(doc);
    hoedown_buffer_free(ob);

    return 0;
}