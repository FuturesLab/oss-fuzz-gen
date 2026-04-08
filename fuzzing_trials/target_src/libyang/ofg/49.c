#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_49(uint8_t const *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct lyd_node *tree = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Prepare a simple schema to use for validation
    const char *schema = "module test {namespace urn:test;prefix t;yang-version 1.1;"
                         "container cont {leaf leaf1 {type string;}}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Allocate memory for the input data
    char *input_data = malloc(size + 1);
    if (input_data == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into a data tree
    lyd_parse_data_mem(ctx, input_data, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &root);

    // Validate the data tree
    lyd_validate_all(&root, ctx, LYD_VALIDATE_PRESENT, &tree);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(input_data);

    return 0;
}