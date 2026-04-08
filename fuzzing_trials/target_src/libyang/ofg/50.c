#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/validation.h"
#include "/src/libyang/build/libyang/tree.h"
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    struct lyd_node *result_tree = NULL;
    LY_ERR err;

    // Create a new libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for the input data
    char *input_data = malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Copy the input data and null-terminate it
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into a data tree
    err = lyd_parse_data_mem(ctx, input_data, LYD_JSON, LYD_PARSE_ONLY, 0, &tree);
    if (err != LY_SUCCESS) {
        free(input_data);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Validate the entire data tree
    err = lyd_validate_all(&tree, ctx, 0, &result_tree);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Validation failed\n");
    }

    // Cleanup
    lyd_free_all(tree);
    lyd_free_all(result_tree);
    ly_ctx_destroy(ctx);
    free(input_data);

    return 0;
}