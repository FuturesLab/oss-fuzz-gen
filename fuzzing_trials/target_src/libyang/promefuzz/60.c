// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_new_meta at tree_data_new.c:789:1 in tree_data.h
// lyd_find_meta at tree_data.c:3138:1 in tree_data.h
// lyd_change_meta at tree_data_new.c:1224:1 in tree_data.h
// lyd_compare_meta at tree_data.c:1892:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// lyd_free_meta_siblings at tree_data_free.c:81:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree_data.h"

static struct ly_ctx *create_dummy_context() {
    return NULL; // Return NULL as we cannot create a real context without libyang's API
}

static struct lyd_node *create_dummy_lyd_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (node) {
        memset(node, 0, sizeof(struct lyd_node));
        // Initialize schema to prevent invalid access
        node->schema = (const struct lysc_node *)malloc(sizeof(struct lysc_node));
        if (node->schema) {
            memset((void *)node->schema, 0, sizeof(struct lysc_node));
        }
    }
    return node;
}

static struct lys_module *create_dummy_lys_module(struct ly_ctx *ctx) {
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    if (module) {
        memset(module, 0, sizeof(struct lys_module));
        // Initialize context to prevent invalid access
        module->ctx = ctx;
    }
    return module;
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = create_dummy_context();
    struct lyd_node *parent = create_dummy_lyd_node();
    struct lys_module *module = create_dummy_lys_module(ctx);
    struct lyd_meta *meta = NULL;
    char *name = NULL;
    char *val_str = NULL;
    uint32_t options = 0;

    if (Size > 0) {
        name = strndup((const char *)Data, Size);
        val_str = strndup((const char *)Data, Size);
    }

    // Fuzzing lyd_new_meta
    if (ctx && (parent || module)) {
        lyd_new_meta(ctx, parent, module, name, val_str, options, &meta);
    }

    // Fuzzing lyd_find_meta
    if (meta) {
        lyd_find_meta(meta, module, name);
    }

    // Fuzzing lyd_change_meta
    if (meta) {
        lyd_change_meta(meta, val_str);
    }

    // Fuzzing lyd_compare_meta
    struct lyd_meta *meta2 = NULL;
    if (meta) {
        lyd_compare_meta(meta, meta2);
    }

    // Cleanup
    if (meta) {
        lyd_free_meta_single(meta);
    }
    lyd_free_meta_siblings(meta2);
    free(name);
    free(val_str);
    if (parent) {
        free((void *)parent->schema);
    }
    free(parent);
    if (module) {
        free(module);
    }

    return 0;
}