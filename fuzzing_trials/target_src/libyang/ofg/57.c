#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Initialize the context
    struct ly_ctx *ctx = NULL;
    LY_ERR err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy module
    const char *module_data = "module example {namespace \"urn:example\"; prefix ex;}";
    struct lys_module *module = lys_parse_mem(ctx, module_data, LYS_IN_YANG, NULL);
    if (!module) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a dummy node
    struct lyd_node *node = lyd_new_path(NULL, ctx, "/example:leaf", "value", 0, 0);
    if (!node) {
        fprintf(stderr, "Failed to create node\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare metadata variables
    struct lyd_meta *meta = NULL;
    const char *meta_name = "meta-name";
    const char *meta_value = "meta-value";
    uint32_t meta_flags = 0;

    // Call the function under test
    err = lyd_new_meta(ctx, node, module, meta_name, meta_value, meta_flags, &meta);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_meta failed\n");
    }

    // Clean up
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}