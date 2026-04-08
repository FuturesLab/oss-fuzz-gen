#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/libyang.h"
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/context.h"

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const struct lysc_node *schema_node = NULL;
    struct lyd_node *result_node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse some schema to get a valid schema node (assuming the schema is valid)
    const char *schema = "module test {namespace urn:test;prefix t; leaf myleaf {type string;}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Find the schema node for "myleaf"
    schema_node = lys_find_path(ctx, NULL, "/test:myleaf", 0);
    if (!schema_node) {
        fprintf(stderr, "Failed to find schema node\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the input data
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the data into a data tree
    err = lyd_parse_data_mem(ctx, input_data, LYD_JSON, LYD_PARSE_ONLY, 0, &root);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
        free(input_data);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_find_sibling_val(root, schema_node, input_data, 0, &result_node);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(input_data);

    return 0;
}