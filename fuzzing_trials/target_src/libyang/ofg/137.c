#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/libyang/build/libyang/libyang.h" // Include the main libyang header
#include "/src/libyang/build/libyang/tree_data.h"
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context\n");
        return 0;
    }

    // Ensure data is null-terminated for parsing
    char *data_copy = (char *)malloc(size + 1);
    if (!data_copy) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Parse the input data into a libyang data tree
    err = lyd_parse_data_mem(ctx, data_copy, LYD_JSON, LYD_PARSE_ONLY, 0, &node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
    }

    // Free the data tree using the function under test
    lyd_free_all(node);

    // Clean up
    free(data_copy);
    ly_ctx_destroy(ctx);

    return 0;
}