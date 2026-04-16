#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hoextdown/src/document.h"  // Correct path for hoedown_document and hoedown_link_type
#include "/src/hoextdown/src/buffer.h"    // Include buffer header for hoedown_buffer
#include "/src/hoextdown/src/html.h"      // Include html header for hoedown_html_renderer_new and hoedown_html_renderer_free

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Create a renderer (assuming a default renderer exists)
    const hoedown_renderer *renderer = hoedown_html_renderer_new(0, 0);

    // Initialize a hoedown_document object with required parameters
    hoedown_document *doc = hoedown_document_new(
        renderer,                // renderer
        0,                       // extensions (use 0 for no extensions)
        16,                      // max_nesting (use a default value, e.g., 16)
        0,                       // attr_activation (use 0 for default)
        NULL,                    // user_block (use NULL for default)
        NULL                     // meta (use NULL for default)
    );

    // Ensure the document is not NULL
    if (doc == NULL) {
        hoedown_html_renderer_free(renderer);
        return 0;
    }

    // Create a buffer for the input data
    uint8_t *buffer = (uint8_t *)malloc(size + 1);
    if (buffer == NULL) {
        hoedown_document_free(doc);
        hoedown_html_renderer_free(renderer);
        return 0;
    }

    // Copy the input data into the buffer
    memcpy(buffer, data, size);
    buffer[size] = '\0';  // Null-terminate the buffer

    // Create an output buffer for rendering
    hoedown_buffer *ob = hoedown_buffer_new(64);

    // Process the document with the input data
    hoedown_document_render(doc, ob, buffer, size);

    // Call the function-under-test
    hoedown_link_type link_type = hoedown_document_link_type(doc);

    // Clean up
    hoedown_buffer_free(ob);
    free(buffer);
    hoedown_document_free(doc);
    hoedown_html_renderer_free(renderer);

    return 0;
}