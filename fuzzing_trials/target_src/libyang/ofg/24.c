#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"  // Include for ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/parser_data.h"  // Include for lyd_parse_data_mem and LYD_PARSE_ONLY
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Ensure data is null-terminated for parsing
    char *data_copy = (char *)malloc(size + 1);
    if (!data_copy) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Parse the data into a lyd_node
    err = lyd_parse_data_mem(ctx, data_copy, LYD_JSON, LYD_PARSE_ONLY, 0, &node);
    free(data_copy);

    if (err == LY_SUCCESS && node != NULL) {
        // Call the function-under-test
        lyd_parse_opaq_error(node);

        // Free the parsed node
        lyd_free_all(node);
    }

    // Destroy the libyang context
    ly_ctx_destroy(ctx);

    return 0;
}