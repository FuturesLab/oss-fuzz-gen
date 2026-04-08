#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct ly_in *in = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;
    const char *module_name = "test-module";
    LYD_FORMAT format = LYD_JSON;
    uint32_t options = 0;
    uint32_t line = 0;
    uint32_t col = 0;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context\n");
        return 0;
    }

    // Create a new input handler
    err = ly_in_new_memory((const char *)data, &in);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create input handler\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_parse_value_fragment(ctx, module_name, in, format, options, line, col, &node);

    // Clean up
    lyd_free_all(node);
    ly_in_free(in, 0);
    ly_ctx_destroy(ctx);

    return 0;
}