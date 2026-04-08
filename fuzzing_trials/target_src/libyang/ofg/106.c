#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include "/src/libyang/src/tree_data.h" // Correct path for libyang functions
#include "/src/libyang/src/context.h" // Include for ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/parser_data.h" // Include for lyd_parse_data_mem
#include "/src/libyang/src/parser_schema.h" // Include for lys_parse_mem

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node1 = NULL;
    struct lyd_node *node2 = NULL;
    struct lyd_node *result = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy schema to parse the data
    const char *schema = "module example {namespace urn:example;prefix ex;container top {leaf a {type string;} leaf b {type string;}}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Prepare data for parsing
    char *data_str = malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Parse the data into a data tree
    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, LYD_PARSE_STRICT, 0, &node1);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
        ly_ctx_destroy(ctx);
        free(data_str);
        return 0;
    }

    // Call the function-under-test
    err = lyd_find_sibling_first(node1, node2, &result);

    // Clean up
    lyd_free_all(node1);
    ly_ctx_destroy(ctx);
    free(data_str);

    return 0;
}