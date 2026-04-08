#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    struct lyd_node *first_sibling = NULL;
    const char *path = "/example-module:container/leaf";
    const void *value = "example-value";
    uint64_t value_type = 0; // Set to a valid value type
    uint32_t options = 0; // Set to appropriate options
    uint32_t hints = 0; // Set to appropriate hints
    LY_ERR err;

    // Initialize the context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    // Ensure the data is not NULL and has a minimum size
    if (data == NULL || size == 0) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_new_path2(parent, ctx, path, value, value_type, options, hints, &new_node, &first_sibling);

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);

    return 0;
}