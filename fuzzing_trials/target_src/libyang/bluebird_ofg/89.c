#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"  // Correct path for the required declarations
#include "/src/libyang/src/context.h"  // Include context-related functions
#include "/src/libyang/src/parser_schema.h"  // Include schema parsing functions

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node1 = NULL;
    struct lyd_node *node2 = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create dummy schemas to allow node creation
    const char *schema = "module a {namespace urn:a;prefix a; leaf x {type string;} leaf y {type string;}}";
    struct lys_module *mod = NULL;
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &mod);
    if (err != LY_SUCCESS || !mod) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create dummy data trees
    err = lyd_new_path(NULL, ctx, "/a:x", "value1", 0, &node1);
    if (err != LY_SUCCESS || !node1) {
        fprintf(stderr, "Failed to create node1\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    err = lyd_new_path(NULL, ctx, "/a:y", "value2", 0, &node2);
    if (err != LY_SUCCESS || !node2) {
        fprintf(stderr, "Failed to create node2\n");
        lyd_free_all(node1);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Fuzz target function
    err = lyd_insert_after(node1, node2);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to insert node2 after node1\n");
        lyd_free_all(node1);
        lyd_free_all(node2);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Clean up
    lyd_free_all(node1);
    ly_ctx_destroy(ctx);

    return 0;
}