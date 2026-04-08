#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    int compiled_size = ly_ctx_compiled_size(ctx);

    // Print the compiled size for debugging purposes
    printf("Compiled size: %d\n", compiled_size);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}