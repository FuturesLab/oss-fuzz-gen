#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Added for uint8_t
#include "/src/libyang/src/validation.h" // Correct path for libyang functions
#include "/src/libyang/build/libyang/context.h"
#include "/src/libyang/build/libyang/tree.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;
    uint32_t options = 0;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a module into the context (using a dummy module for demonstration)
    const char *schema = "module dummy {namespace \"urn:dummy\"; prefix d; leaf dummy-leaf {type string;}}";
    err = lys_parse_mem(ctx, schema, LYS_IN_YANG, &module);
    if (err != LY_SUCCESS || !module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a data tree from the input data
    char *data_str = (char *)malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    err = lyd_parse_data_mem(ctx, data_str, LYD_JSON, LYD_PARSE_ONLY, 0, &root);
    free(data_str);

    if (err != LY_SUCCESS || !root) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    lyd_validate_module_final(root, module, options);

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);

    return 0;
}