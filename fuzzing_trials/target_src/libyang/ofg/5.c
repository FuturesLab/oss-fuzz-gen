#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct lyd_node *new_node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *path = malloc(size + 1);
    if (!path) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(path, data, size);
    path[size] = '\0';

    // Use a simple value for the value parameter
    const char *value = "example_value";

    // Call the function-under-test
    err = lyd_new_path(root, ctx, path, (void *)value, 0, &new_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_path failed\n");
    }

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(path);

    return 0;
}