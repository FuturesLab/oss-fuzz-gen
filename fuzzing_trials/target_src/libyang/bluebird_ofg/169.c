#include "/src/libyang/src/tree_data.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct lyd_node *new_node = NULL;
    LY_ERR err;

    // Create a new libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *path = (char *)malloc(size + 1);
    if (!path) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(path, data, size);
    path[size] = '\0';

    // Use a default value for the value parameter
    const char *value = "default_value";

    // Call the function under test
    lyd_new_path(root, ctx, path, value, 0, &new_node);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(path);

    return 0;
}