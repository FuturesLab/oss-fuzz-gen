#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/in.h"
#include "/src/libyang/src/context.h"

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct ly_in *input = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Initialize the input structure
    ly_in_new_memory((const char *)data, &input);
    if (!input) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_parse_value_fragment(ctx, NULL, input, LYD_XML, 0, 0, 0, &node);

    // Clean up
    lyd_free_all(node);
    ly_in_free(input, 0);
    ly_ctx_destroy(ctx);

    return 0;
}