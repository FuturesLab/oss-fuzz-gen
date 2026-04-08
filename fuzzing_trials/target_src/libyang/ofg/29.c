#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Added for uint8_t
#include "/src/libyang/src/in.h" // Include for input parsing functions
#include "/src/libyang/build/libyang/context.h" // Include for context functions
#include "/src/libyang/build/libyang/tree.h" // Include for tree manipulation functions
#include "/src/libyang/src/validation.h" // Include for validation functions

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *result_node = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse a module to get a valid lys_module
    const char *schema = "module test {namespace \"urn:test\"; prefix t; leaf test-leaf {type string;}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the data and ensure it's null-terminated
    char *data_copy = (char *)malloc(size + 1);
    if (!data_copy) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Parse the data into a lyd_node
    err = lyd_parse_data_mem(ctx, data_copy, LYD_JSON, LYD_PARSE_ONLY, LYD_VALIDATE_PRESENT, &node);
    free(data_copy);

    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Validate the module with the parsed data
    err = lyd_validate_module(&node, module, 0, &result_node);

    // Clean up
    lyd_free_all(node);
    lyd_free_all(result_node);
    ly_ctx_destroy(ctx);

    return 0;
}