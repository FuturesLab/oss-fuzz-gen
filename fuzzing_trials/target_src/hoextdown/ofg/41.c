#include <stdint.h>
#include <stdlib.h>
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/buffer.h"
#include "/src/hoextdown/src/html.h"

// Fuzzing harness for hoedown_document_blockquote_depth
int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure that data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a hoedown_renderer object
    hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);

    // Create a hoedown_buffer object for meta
    hoedown_buffer *meta = hoedown_buffer_new(64);

    // Create a hoedown_document object
    hoedown_document *doc = hoedown_document_new(renderer, 0, 16, 0, NULL, meta);

    // Ensure that the document is created successfully
    if (doc == NULL) {
        hoedown_html_renderer_free(renderer);
        hoedown_buffer_free(meta);
        return 0;
    }

    // Call the function-under-test
    int depth = hoedown_document_blockquote_depth(doc);

    // Clean up
    hoedown_document_free(doc);
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(meta);

    return 0;
}