#include <stdint.h>
#include <stdlib.h>
#include "/src/hoextdown/src/document.h" // Correct path for hoedown_renderer

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int level = *(int*)data;

    // Call the function-under-test
    hoedown_renderer *renderer = hoedown_html_toc_renderer_new(level);

    // Clean up if necessary
    if (renderer != NULL) {
        // Assuming there's a function to free the renderer (if needed)
        // hoedown_renderer_free(renderer);
    }

    return 0;
}