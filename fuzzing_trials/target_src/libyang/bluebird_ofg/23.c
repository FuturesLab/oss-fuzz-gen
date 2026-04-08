#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *search_dir = (char *)malloc(size + 1);
    if (!search_dir) {
        return 0;
    }
    memcpy(search_dir, data, size);
    search_dir[size] = '\0';

    uint32_t options = 0; // Default options, can be varied for more extensive testing
    struct ly_ctx *ctx = NULL;

    // Call the function-under-test
    LY_ERR result = ly_ctx_new(search_dir, options, &ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    free(search_dir);

    return 0;
}