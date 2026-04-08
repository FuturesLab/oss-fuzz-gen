#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/src/validation.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree.h"

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *ext_node = NULL;
    const struct lysc_ext_instance *ext = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy node for testing
    err = lyd_new_path(NULL, ctx, "/ietf-interfaces:interfaces/interface[name='eth0']", NULL, 0, &node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create a new path\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_validate_ext(&node, ext, 0, &ext_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_validate_ext failed\n");
    }

    // Clean up
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}