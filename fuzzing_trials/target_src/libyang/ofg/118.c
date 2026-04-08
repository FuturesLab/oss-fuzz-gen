#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the size is sufficient for a uint32_t
    if (size < sizeof(uint32_t)) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Extract a uint32_t value from the data
    uint32_t options;
    memcpy(&options, data, sizeof(uint32_t));

    // Call the function-under-test
    err = ly_ctx_unset_options(ctx, options);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}