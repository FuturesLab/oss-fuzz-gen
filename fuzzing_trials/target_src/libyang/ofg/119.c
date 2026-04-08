#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    uint32_t options;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS || ctx == NULL) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the data is large enough to extract an options value
    if (size < sizeof(uint32_t)) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Extract options from the input data
    options = *((uint32_t *)data);

    // Call the function-under-test
    err = ly_ctx_unset_options(ctx, options);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}