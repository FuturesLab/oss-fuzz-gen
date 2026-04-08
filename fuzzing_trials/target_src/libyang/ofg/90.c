#include <stdio.h>
#include <stdlib.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    ly_ctx_free_parsed(ctx);

    // Destroy the context
    ly_ctx_destroy(ctx);

    return 0;
}