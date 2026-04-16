#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/buffer.h"

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Initialize necessary variables for the function call
    hoedown_renderer renderer;
    hoedown_extensions extensions = (hoedown_extensions)(data[0] % 256); // Ensure valid enum value
    size_t max_nesting = size > 1 ? data[1] : 16; // Use a default value if size is insufficient
    uint8_t toc_level = size > 2 ? data[2] : 0; // Use a default value if size is insufficient
    hoedown_user_block user_block = NULL; // Assuming no custom user block for simplicity
    hoedown_buffer *buffer = hoedown_buffer_new(64); // Create a buffer with a size of 64

    // Call the function-under-test
    hoedown_document *doc = hoedown_document_new(&renderer, extensions, max_nesting, toc_level, user_block, buffer);

    // Clean up
    if (doc != NULL) {
        hoedown_document_free(doc);
    }
    hoedown_buffer_free(buffer);

    return 0;
}