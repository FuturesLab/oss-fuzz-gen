#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/in.h"
#include "/src/libyang/src/parser_data.h" // Include for lyd_parse_data_mem and LYD_PARSE_OPAQ

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *input_data = malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Copy the fuzzer data into the buffer and null-terminate it
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data as a YANG data tree
    err = lyd_parse_data_mem(ctx, input_data, LYD_JSON, LYD_PARSE_OPAQ, 0, &root); // Changed LYD_PARSE_STRICT to LYD_PARSE_OPAQ
    if (err == LY_SUCCESS && root) {
        // Call the function-under-test with the parsed data tree
        lyd_leafref_link_node_tree(root);

        // Free the data tree
        lyd_free_all(root);
    }

    // Clean up
    free(input_data);
    ly_ctx_destroy(ctx);

    return 0;
}