#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    uint32_t options = 0;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure data size is sufficient to extract a uint32_t value
    if (size >= sizeof(uint32_t)) {
        // Extract a uint32_t value from the input data
        options = *((uint32_t *)data);
    }

    // Call the function-under-test
    ly_ctx_unset_searchdir_last(ctx, options);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}