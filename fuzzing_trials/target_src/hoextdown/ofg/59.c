#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/html.h"

// Function-under-test
hoedown_link_type hoedown_document_link_type(hoedown_document *doc);

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize hoedown renderer
    hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);

    // Create a hoedown buffer for meta
    hoedown_buffer *meta = hoedown_buffer_new(64);

    // Create a hoedown document with all required parameters
    hoedown_document *doc = hoedown_document_new(renderer, 0, 16, 0, NULL, meta);

    // Ensure doc is not NULL
    if (doc != NULL) {
        // Call the function-under-test
        hoedown_link_type link_type = hoedown_document_link_type(doc);

        // Optionally use link_type to avoid compiler warnings
        (void)link_type;

        // Free the hoedown document
        hoedown_document_free(doc);
    }

    // Free the renderer
    hoedown_html_renderer_free(renderer);

    // Free the buffer
    hoedown_buffer_free(meta);

    return 0;
}