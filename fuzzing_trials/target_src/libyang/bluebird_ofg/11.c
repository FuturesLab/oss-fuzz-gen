#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_schema.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    LY_ERR err;
    const char *schema = "module example {namespace urn:example;prefix ex;container parent {leaf child {type string;}}}";

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the schema
    struct lys_module *mod = NULL;
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &mod);
    if (err != LY_SUCCESS || !mod) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Ensure input data is not empty
    if (size == 0) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a parent node from the schema
    err = lyd_new_path(NULL, ctx, "/example:parent", NULL, 0, &parent);
    if (err != LY_SUCCESS || !parent) {
        fprintf(stderr, "Failed to create parent node\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a child node from the input data
    char *data_str = malloc(size + 1);
    if (!data_str) {
        lyd_free_tree(parent);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    struct lyd_node *child = NULL;
    err = lyd_new_path(parent, ctx, "/example:parent/child", data_str, 0, &child);
    if (err != LY_SUCCESS || !child) {
        fprintf(stderr, "Failed to create child node\n");
        free(data_str);
        lyd_free_tree(parent);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Clean up
    free(data_str);
    lyd_free_tree(parent);
    ly_ctx_destroy(ctx);

    return 0;
}