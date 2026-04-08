#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = "/tmp"; // A non-NULL directory path
    uint32_t options = 0; // Default options

    // Call the function-under-test
    LY_ERR result = ly_ctx_new(search_dir, options, &ctx);

    // Ensure the context is freed if it was successfully created
    if (result == LY_SUCCESS && ctx != NULL) {
        ly_ctx_destroy(ctx);
    }

    return 0;
}