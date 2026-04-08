#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    struct lyd_node *parent = NULL;
    struct lyd_node *first_sibling = NULL;
    struct lyd_node *new_node = NULL;
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Ensure that the input data is a valid NULL-terminated string
    char *path = (char *)malloc(size + 1);
    if (!path) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(path, data, size);
    path[size] = '\0';

    // Create a dummy value for the void pointer
    const char *value = "dummy_value";

    // Call the function-under-test
    lyd_new_path2(parent, ctx, path, value, 0, 0, 0, &first_sibling, &new_node);

    // Clean up
    free(path);
    lyd_free_all(first_sibling);
    ly_ctx_destroy(ctx);

    return 0;
}