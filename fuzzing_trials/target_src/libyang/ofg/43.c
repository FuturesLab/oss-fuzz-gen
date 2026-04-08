#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_schema.h"

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    const struct lys_module *module = NULL;
    char *module_name = "example-module";
    char *term_name = "example-term";
    char *term_value = NULL;
    uint32_t options = 0;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Load a sample module
    err = lys_parse_mem(ctx, "module example-module {namespace urn:example;prefix ex; leaf example-term {type string;}}", LYS_IN_YANG, (struct lys_module **)&module);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse module\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for term_value and copy fuzz data
    term_value = (char *)malloc(size + 1);
    if (!term_value) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(term_value, data, size);
    term_value[size] = '\0';

    // Call the function-under-test
    err = lyd_new_term(parent, module, term_name, term_value, options, &new_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_term failed\n");
    }

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);
    free(term_value);

    return 0;
}