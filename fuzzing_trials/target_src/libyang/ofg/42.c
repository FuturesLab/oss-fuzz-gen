#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *src_sibling = NULL;
    struct lyd_node *dup_sibling = NULL;
    struct lyd_node *parent = NULL;
    LY_ERR err;
    uint32_t options = 0;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the input data into a data tree
    char *data_str = malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &src_sibling);
    free(data_str);

    if (err != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Fuzz the lyd_dup_siblings_to_ctx function
    err = lyd_dup_siblings_to_ctx(src_sibling, ctx, parent, options, &dup_sibling);

    // Cleanup
    lyd_free_all(src_sibling);
    lyd_free_all(dup_sibling);
    ly_ctx_destroy(ctx);

    return 0;
}