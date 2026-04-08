#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/parser_data.h"  // Include for lyd_parse_data_mem and LYD_PARSE_ONLY
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Ensure data is null-terminated
    char *data_copy = (char *)malloc(size + 1);
    if (!data_copy) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Parse the data to create a data tree node
    lyd_parse_data_mem(ctx, data_copy, LYD_XML, LYD_PARSE_ONLY, 0, &node);

    // Call the function-under-test
    module = lyd_node_module(node);

    // Clean up
    lyd_free_all(node);
    ly_ctx_destroy(ctx);
    free(data_copy);

    return 0;
}