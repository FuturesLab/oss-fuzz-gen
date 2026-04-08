#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <stdint.h> // Include for uint8_t
#include "/src/libyang/src/context.h" // For ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/tree_data.h" // For lyd_node, lyd_free_all, lyd_parse_data_mem
#include "/src/libyang/src/validation.h" // For lyd_validate_op

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *tree = NULL;
    LY_ERR err;
    uint32_t op_type = 0; // Assuming a valid enumeration value

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the input data into a libyang data tree
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    err = lyd_parse_data_mem(ctx, data_copy, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &node);
    if (err != LY_SUCCESS) {
        free(data_copy);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_validate_op(node, NULL, op_type, &tree);

    // Clean up
    lyd_free_all(node);
    lyd_free_all(tree);
    ly_ctx_destroy(ctx);
    free(data_copy);

    return 0;
}