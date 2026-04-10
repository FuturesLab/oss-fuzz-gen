#include <stdint.h>
#include <stddef.h>
#include "document.h"
#include "/src/hoextdown/src/buffer.h"

// Define a simple renderer to pass to hoedown_document_new
static void dummy_blockcode(hoedown_buffer *ob, const hoedown_buffer *text, const hoedown_buffer *lang, const hoedown_renderer_data *data) {}
static void dummy_blockquote(hoedown_buffer *ob, const hoedown_buffer *text, const hoedown_renderer_data *data) {}
static void dummy_header(hoedown_buffer *ob, const hoedown_buffer *text, int level, const hoedown_renderer_data *data) {}
static void dummy_paragraph(hoedown_buffer *ob, const hoedown_buffer *text, const hoedown_renderer_data *data) {}
static void dummy_linebreak(hoedown_buffer *ob, const hoedown_renderer_data *data) {}

static hoedown_renderer renderer = {
    /* block level callbacks */
    dummy_blockcode,
    dummy_blockquote,
    dummy_header,
    dummy_paragraph,
    dummy_linebreak,
    /* span level callbacks */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /* low level callbacks */
    NULL, NULL, NULL, NULL,
    /* renderer data */
    NULL
};

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize hoedown_renderer
    hoedown_document *document = hoedown_document_new(&renderer, 0, 16, 0, NULL, NULL);

    // Ensure document is not NULL
    if (document == NULL) {
        return 0;
    }

    // Ensure data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        hoedown_document_free(document);
        return 0;
    }

    // Create a buffer to hold the input data
    hoedown_buffer *input_buffer = hoedown_buffer_new(size);
    if (input_buffer == NULL) {
        hoedown_document_free(document);
        return 0;
    }

    // Copy the input data into the buffer
    hoedown_buffer_put(input_buffer, data, size);

    // Use the function-under-test: render the document
    hoedown_buffer *output_buffer = hoedown_buffer_new(64);
    if (output_buffer == NULL) {
        hoedown_buffer_free(input_buffer);
        hoedown_document_free(document);
        return 0;
    }
    hoedown_document_render(document, output_buffer, input_buffer->data, input_buffer->size);

    // Clean up
    hoedown_buffer_free(output_buffer);
    hoedown_buffer_free(input_buffer);
    hoedown_document_free(document);

    return 0;
}