#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the input data as a JSON data tree
    char *json_data = (char *)malloc(size + 1);
    if (!json_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    // Attempt to parse the data
    lyd_parse_data_mem(ctx, json_data, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &root);

    // Call the function-under-test
    module = lyd_owner_module(root);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(json_data);

    return 0;
}