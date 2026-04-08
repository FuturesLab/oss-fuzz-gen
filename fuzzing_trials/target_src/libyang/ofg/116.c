#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include "/src/libyang/src/tree_data.h"  // Correct header for lyd_new_inner
#include "/src/libyang/src/context.h"    // Correct header for ly_ctx_new
#include "/src/libyang/src/tree_schema.h" // Correct header for lys_parse_mem
#include "/src/libyang/src/parser_schema.h" // Include for lys_parse_mem

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
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

    // Load a module for testing
    err = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t;}", LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Ensure data is null-terminated for string operations
    char *data_str = (char *)malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Call the function-under-test
    lyd_new_inner(parent, module, data_str, 1, &new_node);

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);
    free(data_str);

    return 0;
}