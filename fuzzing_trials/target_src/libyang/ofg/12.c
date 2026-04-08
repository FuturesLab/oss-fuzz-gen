#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    const char *yanglib_data = "example-yang-library-data";
    void *user_data = (void *)0x1;  // Just a non-NULL pointer for testing

    // Initialize libyang context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context\n");
        return 0;
    }

    // Call the function under test
    LY_ERR result = ly_ctx_get_yanglib_data(ctx, &node, yanglib_data, user_data);

    // Clean up
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}