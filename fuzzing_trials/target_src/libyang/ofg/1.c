#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the input size is sufficient for meaningful data extraction
    if (size < 4) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create buffers for strings and ensure null-termination
    char name[2];
    char module_name[2];
    char value[2];

    name[0] = data[0];
    name[1] = '\0';

    module_name[0] = data[1];
    module_name[1] = '\0';

    value[0] = data[2];
    value[1] = '\0';

    const char *value_prefix = "example-prefix"; // This can be constant or derived similarly

    // Call the function-under-test
    err = lyd_new_opaq2(parent, ctx, name, module_name, value, value_prefix, &new_node);

    // Clean up resources
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);

    return 0;
}