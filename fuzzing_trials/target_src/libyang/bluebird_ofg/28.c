#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <stdint.h> // Include for uint8_t
#include "/src/libyang/src/tree_data.h" // Correct path for the necessary declarations
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree.h"
#include "/src/libyang/src/parser_schema.h" // Include for lys_parse_mem

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a module to get a valid lys_module pointer
    err = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t; list mylist {key id; leaf id {type string;}}}", LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Ensure data is null-terminated and non-NULL
    char *name = (char *)malloc(size + 1);
    if (!name) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    err = lyd_new_list2(parent, module, "mylist", name, 0, &new_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_list2 failed\n");
    }

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);
    free(name);

    return 0;
}