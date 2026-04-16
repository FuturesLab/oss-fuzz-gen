#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy
#include "/src/hoextdown/src/document.h"
#include "/src/hoextdown/src/html.h" // Correct path for html.h

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a renderer
    if (size < sizeof(hoedown_renderer)) {
        return 0;
    }

    // Allocate memory for hoedown_renderer
    hoedown_renderer *renderer = (hoedown_renderer *)malloc(sizeof(hoedown_renderer));
    if (renderer == NULL) {
        return 0;
    }

    // Initialize the renderer with some data
    // Assuming data is used to initialize the renderer in some meaningful way
    // Here we simply copy the data into the renderer for fuzzing purposes
    memcpy(renderer, data, sizeof(hoedown_renderer));

    // Call the function-under-test
    hoedown_html_renderer_free(renderer);

    return 0;
}