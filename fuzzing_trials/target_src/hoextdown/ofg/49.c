#include <stdint.h>
#include <stddef.h>
#include "/src/hoextdown/src/html.h"
#include "/src/hoextdown/src/document.h"

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure that the data is large enough to extract meaningful values
    if (size < sizeof(hoedown_html_flags) + sizeof(int)) {
        return 0;
    }

    // Extract hoedown_html_flags and int from the input data
    hoedown_html_flags flags = *(hoedown_html_flags *)data;
    int render_options = *(int *)(data + sizeof(hoedown_html_flags));

    // Call the function-under-test
    hoedown_renderer *renderer = hoedown_html_renderer_new(flags, render_options);

    // Clean up if necessary
    if (renderer != NULL) {
        hoedown_html_renderer_free(renderer);
    }

    return 0;
}