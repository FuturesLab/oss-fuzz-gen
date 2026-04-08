#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    ly_bool result;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    result = ly_ctx_is_printed(ctx);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}