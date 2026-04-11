#include <stdint.h>
#include <stdlib.h>
#include "/src/hoextdown/src/html.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure the size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an int from the input data
    int level = *(int *)data;

    // Call the function-under-test with the extracted int
    hoedown_renderer *renderer = hoedown_html_toc_renderer_new(level);

    // Clean up if necessary
    if (renderer != NULL) {
        hoedown_html_renderer_free(renderer);
    }

    return 0;
}