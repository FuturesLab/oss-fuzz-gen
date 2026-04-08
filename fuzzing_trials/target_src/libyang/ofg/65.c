#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *target_node = NULL;
    struct lyd_node *source_node = NULL;
    const struct lys_module *module = NULL;
    lyd_merge_cb merge_cb = NULL;
    void *private_data = NULL;
    uint16_t options = 0;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse a module to get a lys_module object
    const char *schema = "module test {namespace urn:test;prefix t;leaf leaf1 {type string;}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Parse data to create a source_node
    char *data_str = malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &source_node);
    free(data_str);

    if (err != LY_SUCCESS || !source_node) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_merge_module(&target_node, source_node, module, merge_cb, private_data, options);

    // Clean up
    lyd_free_all(target_node);
    lyd_free_all(source_node);
    ly_ctx_destroy(ctx);

    return 0;
}