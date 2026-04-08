#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/parser_schema.h"

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    struct lyd_node *result = NULL;
    const struct lysc_node *schema_node = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy schema and data for testing
    const char *schema = "module test {namespace urn:test;prefix t; leaf test-leaf {type string;}}";
    const char *data_str = "<test-leaf xmlns=\"urn:test\">test</test-leaf>";

    // Parse the schema
    struct lys_module *mod = NULL;
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &mod);
    if (err != LY_SUCCESS || !mod) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Parse the data
    err = lyd_parse_data_mem(ctx, data_str, LYD_XML, 0, LYD_VALIDATE_PRESENT, &tree);
    if (err != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Find the schema node for the leaf
    schema_node = lys_find_path(ctx, NULL, "/test:test-leaf", 0);
    if (!schema_node) {
        lyd_free_all(tree);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare a string from the input data
    char *value = malloc(size + 1);
    if (!value) {
        lyd_free_all(tree);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    // Call the function-under-test
    lyd_find_sibling_val(tree, schema_node, value, 0, &result);

    // Clean up
    free(value);
    lyd_free_all(tree);
    ly_ctx_destroy(ctx);

    return 0;
}