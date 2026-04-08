#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL, *result = NULL;
    const char *schema = "module test {namespace urn:test;prefix t;container c {leaf l {type string;}}}";
    const char *data_str = "<c xmlns=\"urn:test\"><l>value</l></c>";

    // Initialize libyang context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse schema
    if (lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL) == NULL) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Parse data
    if (lyd_parse_data_mem(ctx, data_str, LYD_XML, 0, LYD_VALIDATE_PRESENT, &root) != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse data\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare a string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        lyd_free_all(root);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Call the function-under-test
    lyd_find_sibling_opaq_next(root, input_str, &result);

    // Clean up
    free(input_str);
    lyd_free_all(root);
    ly_ctx_destroy(ctx);

    return 0;
}