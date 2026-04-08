#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    uint32_t module_count = ly_ctx_internal_modules_count(ctx);

    // Print the module count for debugging purposes
    printf("Internal module count: %u\n", module_count);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}