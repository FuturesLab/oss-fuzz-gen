#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/parser_schema.h"

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const char *schema = "module example {namespace \"urn:example\";prefix ex; leaf test {type string;}}";
    const char *xpath = "/example:test";
    struct lyxp_var *vars = NULL;
    ly_bool result = 0;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Parse the schema
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);
    if (err != LY_SUCCESS) {
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

    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, LYD_PARSE_ONLY, 0, &root);
    free(data_str);
    if (err != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lyd_eval_xpath2(root, xpath, vars, &result);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);

    return 0;
}