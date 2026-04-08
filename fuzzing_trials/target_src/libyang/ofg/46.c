#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>  // Include the standard header for uint8_t
#include "libyang.h"

// Include the necessary header for data tree functions
#include "/src/libyang/build/libyang/tree_data.h"
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/build/libyang/context.h"  // Include the header for context functions

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    static bool log = false;
    const char *schema = "module example {namespace urn:example;prefix ex;yang-version 1.1;leaf example-leaf {type string;}}";

    if (!log) {
        ly_log_options(0);
        log = true;
    }

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse a schema to the context
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Compile the context
    err = ly_ctx_compile(ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to compile context\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Attempt to parse the input data as a YANG data tree
    struct lyd_node *data_tree = NULL;
    err = lyd_parse_data_mem(ctx, (const char *)data, size, LYD_XML, LYD_PARSE_ONLY, &data_tree);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data tree\n");
    }

    // Clean up the data tree
    lyd_free_all(data_tree);

    // Clean up the context
    ly_ctx_destroy(ctx);

    return 0;
}