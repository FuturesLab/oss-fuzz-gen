#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;
    char *input_data = NULL;
    const char *schema = "module test {namespace urn:test;prefix t;leaf myleaf {type string;}}";

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse schema
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare input data
    input_data = malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Create a data tree node
    err = lyd_new_path(NULL, ctx, "/test:myleaf", input_data, 0, &node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create data node\n");
        free(input_data);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_change_term_canon(node, input_data);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_change_term_canon failed\n");
    }

    // Cleanup
    lyd_free_all(node);
    free(input_data);
    ly_ctx_destroy(ctx);

    return 0;
}