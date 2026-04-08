#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *data_str = (char *)malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Parse the input data into a YANG data tree
    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, LYD_PARSE_ONLY, 0, &root);
    free(data_str);
    if (err != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    lyd_parse_opaq_error(root);

    // Cleanup
    lyd_free_all(root);
    ly_ctx_destroy(ctx);

    return 0;
}