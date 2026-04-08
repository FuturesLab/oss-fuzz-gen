#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_schema.h" // Include the header for lys_parse_mem

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const struct lys_module *module = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a module to the context
    const char *schema = "module example {namespace urn:example;prefix ex;yang-version 1.1;"
                         "list mylist {key \"name\";leaf name {type string;} leaf value {type string;}}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, (struct lys_module **)&module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare input parameters for lyd_new_list2
    const char *list_name = "mylist";
    const char *key_value = "name";
    uint32_t options = 0;

    // Call the function-under-test
    err = lyd_new_list2(parent, module, list_name, key_value, options, &new_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create new list node\n");
    }

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);

    return 0;
}