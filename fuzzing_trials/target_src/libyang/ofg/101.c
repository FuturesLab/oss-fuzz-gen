#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct ly_set *set = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a simple YANG module for testing
    const char *schema = "module test {namespace urn:test;prefix t;container top {leaf name {type string;}}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse schema\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a data tree from the input data
    char *data_str = malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Fix: Add the missing argument for lyd_parse_data_mem
    err = lyd_parse_data_mem(ctx, data_str, LYD_XML, LYD_PARSE_STRICT, 0, &root);
    free(data_str);

    if (err != LY_SUCCESS || !root) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Use a simple XPath expression to test
    const char *xpath = "/test:top/name";

    // Call the function-under-test
    err = lyd_find_xpath(root, xpath, &set);

    // Clean up
    lyd_free_all(root);
    ly_set_free(set, NULL);
    ly_ctx_destroy(ctx);

    return 0;
}