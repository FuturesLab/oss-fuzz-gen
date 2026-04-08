#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *pattern = "[a-z]*";
    const char *value = NULL;
    uint32_t options = 0;
    void *result = NULL;
    LY_ERR err;

    // Initialize the libyang context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context\n");
        return 0;
    }

    // Allocate memory for the value and ensure it's null-terminated
    value = (const char *)malloc(size + 1);
    if (!value) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy((char *)value, data, size);
    ((char *)value)[size] = '\0';

    // Call the function-under-test
    err = ly_pattern_match(ctx, pattern, value, options, &result);

    // Clean up
    free((char *)value);
    ly_ctx_destroy(ctx);

    return 0;
}