#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/parser_schema.h"

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *original_node = NULL;
    struct lyd_node *dup_node = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy schema to parse the data
    const char *schema = "module test {namespace urn:test;prefix t;container c {leaf l {type string;}}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Convert the fuzz data into a string to be parsed
    char *data_str = malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Parse the data into a data tree
    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, LYD_PARSE_ONLY, 0, &original_node);
    free(data_str);

    if (err == LY_SUCCESS && original_node) {
        // Call the function-under-test
        err = lyd_dup_siblings_to_ctx(original_node, ctx, NULL, 0, &dup_node);
        if (err == LY_SUCCESS) {
            // Free the duplicated node
            lyd_free_all(dup_node);
        } else {
            fprintf(stderr, "Failed to duplicate siblings\n");
        }

        // Free the original node
        lyd_free_all(original_node);
    } else {
        fprintf(stderr, "Failed to parse data into a data tree\n");
    }

    // Destroy the context
    ly_ctx_destroy(ctx);

    return 0;
}