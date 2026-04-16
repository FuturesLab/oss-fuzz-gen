#include <stdint.h>
#include <stddef.h>
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/buffer.h"
#include "/src/hoextdown/src/html.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize the renderer
    hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);

    // Set up extensions, using a non-zero value for fuzzing
    hoedown_extensions extensions = HOEDOWN_EXT_TABLES | HOEDOWN_EXT_FENCED_CODE;

    // Set up max nesting level, using a non-zero value for fuzzing
    size_t max_nesting = 16;

    // Set up a non-zero value for the flags
    uint8_t flags = 1;

    // Initialize a user block, using a non-null value for fuzzing
    hoedown_user_block user_block = {0};

    // Initialize an output buffer
    hoedown_buffer *buffer = hoedown_buffer_new(64);

    // Call the function under test
    hoedown_document *doc = hoedown_document_new(renderer, extensions, max_nesting, flags, user_block, buffer);

    // Feed the document with the input data
    if (doc != NULL && data != NULL && size > 0) {
        hoedown_document_render(doc, buffer, data, size);
    }

    // Clean up
    if (doc != NULL) {
        hoedown_document_free(doc);
    }
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(buffer);

    return 0;
}