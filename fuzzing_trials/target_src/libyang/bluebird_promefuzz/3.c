#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libyang.h"

static struct ly_ctx *initialize_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static struct lys_module *get_module(struct ly_ctx *ctx) {
    // Load a dummy module for testing
    const char *module_data = "module dummy {namespace \"urn:dummy\"; prefix d;}";
    struct lys_module *mod = NULL;
    if (lys_parse_mem(ctx, module_data, LYS_IN_YANG, &mod) != LY_SUCCESS) {
        return NULL;
    }
    return mod;
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    struct ly_ctx *ctx = initialize_context();
    if (!ctx) return 0;

    struct lys_module *module = get_module(ctx);
    if (!module) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    struct lyd_node *parent = NULL;
    struct lyd_node *node = NULL;
    const char *name = "test-node";
    uint32_t options = 0;

    // Ensure value is null-terminated
    char *value = (char *)malloc(Size + 1);
    if (!value) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(value, Data, Size);
    value[Size] = '\0';

    // Fuzzing lyd_new_term
    lyd_new_term(parent, module, name, value, options, &node);

    // Fuzzing lyd_new_opaq
    const char *prefix = "d";
    const char *module_name = "dummy";
    lyd_new_opaq(parent, ctx, name, value, prefix, module_name, &node);

    // Fuzzing lyd_new_list
    lyd_new_list(parent, module, name, options, &node);

    // Fuzzing lyd_new_path
    const char *path = "/dummy:test-node";
    lyd_new_path(parent, ctx, path, value, options, &node);

    // Fuzzing lyd_new_inner
    ly_bool output = 0;
    lyd_new_inner(parent, module, name, output, &node);

    // Fuzzing lyd_new_list3
    const void *key_values[] = {value, NULL};
    uint32_t value_sizes_bits[] = {8};
    lyd_new_list3(parent, module, name, key_values, value_sizes_bits, options, &node);

    // Cleanup
    free(value);
    lyd_free_all(parent);
    ly_ctx_destroy(ctx);

    return 0;
}