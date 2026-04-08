#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for uint8_t
#include "/src/libyang/src/tree_data.h" // Correct path for lyd_free_siblings
#include "/src/libyang/src/context.h" // Correct path for ly_ctx_new and ly_ctx_destroy
#include "/src/libyang/src/tree_schema.h" // Correct path for lys_parse_mem
#include "/src/libyang/src/parser_data.h" // Include for lyd_parse_data_mem and LYD_PARSE_* constants
#include "/src/libyang/src/log.h" // Include for LY_ERR and related definitions

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const char *yang_module = "module test {namespace urn:test;prefix t;leaf name {type string;}}";
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the YANG module
    err = lys_parse_mem(ctx, yang_module, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse YANG module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the data and ensure it's null-terminated
    char *data_mem = (char *)malloc(size + 1);
    if (!data_mem) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_mem, data, size);
    data_mem[size] = '\0';

    // Parse the data to create a data tree
    err = lyd_parse_data_mem(ctx, data_mem, LYD_JSON, LYD_PARSE_STRICT, 0, &root);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
    }

    // Free the siblings
    lyd_free_siblings(root);

    // Clean up
    free(data_mem);
    ly_ctx_destroy(ctx);

    return 0;
}