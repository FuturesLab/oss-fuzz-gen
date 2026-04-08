#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    uint32_t hash = ly_ctx_get_modules_hash(ctx);

    // Use the hash value in some way to avoid compiler optimizing it away
    if (hash == 0) {
        fprintf(stderr, "Hash is zero\n");
    }

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}