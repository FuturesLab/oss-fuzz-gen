#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree.h"
#include "/src/libyang/src/validation.h"
#include "/src/libyang/src/in.h"

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const struct lys_module *mod = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a module into the context
    mod = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t; leaf myleaf {type string;}}", LYS_IN_YANG, NULL);
    if (!mod) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a data tree from the input data
    char *data_str = (char *)malloc(size + 1);
    if (data_str == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    root = lyd_parse_data_mem(ctx, data_str, LYD_JSON, 0, LYD_VALIDATE_PRESENT, NULL);
    free(data_str);

    if (!root) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Fuzz the function-under-test
    lyd_validate_module_final(root, mod, 0);

    // Cleanup
    lyd_free_all(root);
    ly_ctx_destroy(ctx);

    return 0;
}