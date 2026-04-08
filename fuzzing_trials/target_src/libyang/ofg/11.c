#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_data.h"  // Corrected include for lyd_new_list

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    struct lyd_node *parent = NULL;
    struct lyd_node *new_list = NULL;
    struct lys_module *module = NULL;
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    char *name = NULL;
    uint32_t flags = 0;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a module to get a valid lys_module
    err = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t; list mylist {key \"name\"; leaf name {type string;}}}", LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the name, ensuring it's null-terminated
    name = (char *)malloc(size + 1);
    if (!name) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    err = lyd_new_list(parent, module, name, flags, &new_list, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_list failed\n");
    }

    // Clean up
    lyd_free_all(new_list);
    ly_ctx_destroy(ctx);
    free(name);

    return 0;
}