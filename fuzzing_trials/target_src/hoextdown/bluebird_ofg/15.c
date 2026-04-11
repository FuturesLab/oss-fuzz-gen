#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "html.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to test the function
    if (size < 1) return 0;

    // Define a sample tag name to check against
    const char *tag_name = "div";

    // Call the function-under-test
    hoedown_html_tag result = hoedown_html_is_tag(data, size, tag_name);

    // Use the result in some way to avoid compiler optimizations
    if (result == HOEDOWN_HTML_TAG_NONE) {
        // Do something if the result is HOEDOWN_HTML_TAG_NONE
    }

    return 0;
}