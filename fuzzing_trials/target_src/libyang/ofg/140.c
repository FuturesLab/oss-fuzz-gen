#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize the context with some default parameters
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS || ctx == NULL) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Call the function-under-test
    uint16_t change_count = ly_ctx_get_change_count(ctx);

    // Print the change count for debugging purposes (optional)
    printf("Change count: %u\n", change_count);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}