#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> // Include for memcpy
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h" // Include for ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/tree_schema.h" // Include for lys_parse_mem and LYS_IN_YANG
#include "/src/libyang/src/parser_data.h" // Include for lyd_parse_data_mem and LYD_PARSE_ONLY

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *dup_node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy schema for testing
    const char *schema = "module test {namespace urn:test;prefix t; leaf test-leaf {type string;}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Parse the input data as a JSON data tree
    char *json_data = malloc(size + 1);
    if (!json_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    lyd_parse_data_mem(ctx, json_data, LYD_JSON, 0, LYD_PARSE_ONLY, &node);

    // Call the function-under-test
    err = lyd_dup_single(node, parent, 0, &dup_node);

    // Clean up
    lyd_free_all(node);
    lyd_free_all(dup_node);
    ly_ctx_destroy(ctx);
    free(json_data);

    return 0;
}