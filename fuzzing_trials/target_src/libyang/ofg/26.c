#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    uint32_t hash = ly_ctx_get_modules_hash(ctx);

    // Print the hash for debugging purposes
    printf("Modules hash: %u\n", hash);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}