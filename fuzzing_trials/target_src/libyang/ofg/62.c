#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/build/libyang/context.h"
#include "/src/libyang/build/libyang/tree.h"
#include "/src/libyang/build/libyang/set.h"
#include "/src/libyang/build/libyang/parser_schema.h"

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct lyd_node *node = NULL;
    struct lys_module *module = NULL; // Remove const qualifier
    LY_ERR err;
    LY_VALUE_FORMAT format = LY_VALUE_JSON;
    void *prefix_data = NULL;
    const struct lyxp_var *vars = NULL;
    LY_XPATH_TYPE *xpath_type = NULL;
    struct ly_set *set = NULL;
    char *errmsg = NULL;
    long double *ld = NULL;
    ly_bool *flag = NULL;
    char *xpath_expr = NULL;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a sample module to the context
    err = lys_parse_mem(ctx, "module a {namespace urn:a;prefix a;}", LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a sample data tree
    err = lyd_new_path2(NULL, ctx, "/a:leaf", "value", 0, 0, 0, NULL, &root);
    if (err != LY_SUCCESS || !root) {
        fprintf(stderr, "Failed to create data tree\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the xpath expression
    xpath_expr = (char *)malloc(size + 1);
    if (!xpath_expr) {
        lyd_free_all(root);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Copy the input data to the xpath expression
    memcpy(xpath_expr, data, size);
    xpath_expr[size] = '\0';

    // Call the function-under-test
    err = lyd_eval_xpath4(root, node, module, xpath_expr, format, prefix_data, vars, xpath_type, &set, &errmsg, ld, flag);

    // Clean up
    free(xpath_expr);
    lyd_free_all(root);
    ly_set_free(set, NULL);
    ly_ctx_destroy(ctx);

    return 0;
}