#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;

    // Create a context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Define a simple schema for testing
    const char *schema = "module example {namespace urn:example;prefix ex;"
                         "leaf test {type string;}}";

    // Parse the schema
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Create a data tree for testing
    const char *data_json = "{\"example:test\": \"initial\"}";
    err = lyd_parse_data_mem(ctx, data_json, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare the new value for the leaf node
    char *new_value = malloc(size + 1);
    if (!new_value) {
        lyd_free_all(node);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(new_value, data, size);
    new_value[size] = '\0';

    // Call the function-under-test
    lyd_change_term(node, new_value);

    // Clean up
    free(new_value);
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}