#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *child = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Create a dummy schema to parse
    const char *schema = "module test {namespace urn:test;prefix t; container parent {leaf child {type string;}}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Prepare data for the parent node
    char *parent_data = malloc(size + 1);
    if (!parent_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(parent_data, data, size);
    parent_data[size] = '\0';

    // Parse the parent node
    lyd_parse_data_mem(ctx, parent_data, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &parent);
    free(parent_data);

    // Prepare data for the child node
    char *child_data = malloc(size + 1);
    if (!child_data) {
        lyd_free_all(parent);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(child_data, data, size);
    child_data[size] = '\0';

    // Parse the child node
    lyd_parse_data_mem(ctx, child_data, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &child);
    free(child_data);

    // Call the function-under-test
    lyd_insert_child(parent, child);

    // Clean up
    lyd_free_all(parent);
    lyd_free_all(child);
    ly_ctx_destroy(ctx);

    return 0;
}