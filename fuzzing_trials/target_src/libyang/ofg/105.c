#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Added for memcpy
#include "/src/libyang/src/tree_data.h"  // Correct path for lyd_free_tree
#include "/src/libyang/src/context.h"    // Correct path for ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/parser_data.h" // Correct path for lyd_parse_data_mem
#include "/src/libyang/src/parser_schema.h" // Correct path for lys_parse_mem

// Remove the 'extern "C"' linkage specification for C++ and use C linkage
int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Create a schema for the context
    const char *schema = "module fuzzer {namespace urn:fuzzer;prefix fz; leaf test {type string;}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Allocate memory for data and ensure it's null-terminated
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into a data tree
    lyd_parse_data_mem(ctx, input_data, LYD_JSON, LYD_PARSE_ONLY, 0, &tree);

    // Free the data tree using the function-under-test
    lyd_free_tree(tree);

    // Clean up
    free(input_data);
    ly_ctx_destroy(ctx);

    return 0;
}