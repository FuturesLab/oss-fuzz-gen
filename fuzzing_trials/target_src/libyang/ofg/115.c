#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/parser_schema.h" // Include for lys_parse_mem function
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Load a module into the context for testing
    err = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t; container parent { container child; }}", LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a parent node to attach the new node to
    err = lyd_new_inner(NULL, module, "parent", 0, &parent);
    if (err != LY_SUCCESS || !parent) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Convert the input data to a string for the node name
    char *node_name = (char *)malloc(size + 1);
    if (!node_name) {
        lyd_free_all(parent);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(node_name, data, size);
    node_name[size] = '\0';

    // Call the function-under-test
    err = lyd_new_inner(parent, module, node_name, 0, &new_node);

    // Clean up
    free(node_name);
    lyd_free_all(parent);
    ly_ctx_destroy(ctx);

    return 0;
}