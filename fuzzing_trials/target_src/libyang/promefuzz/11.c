// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_change_term_canon at tree_data_new.c:1216:1 in tree_data.h
// lyd_find_sibling_val at tree_data.c:3267:1 in tree_data.h
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_new_meta at tree_data_new.c:789:1 in tree_data.h
// lyd_change_term at tree_data_new.c:1208:1 in tree_data.h
// lyd_new_term at tree_data_new.c:742:1 in tree_data.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h"

static struct ly_ctx *create_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static struct lys_module *get_module(struct ly_ctx *ctx) {
    if (!ctx) {
        return NULL;
    }
    // Create a dummy module with initialized ctx
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    if (module) {
        module->ctx = ctx;
    }
    return module;
}

static struct lyd_node *create_dummy_node(struct ly_ctx *ctx) {
    if (!ctx) {
        return NULL;
    }
    // Create a dummy node with initialized schema
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (node) {
        node->schema = (const struct lysc_node *)malloc(sizeof(struct lysc_node));
        if (node->schema) {
            ((struct lysc_node *)node->schema)->module = (struct lys_module *)malloc(sizeof(struct lys_module));
            if (((struct lysc_node *)node->schema)->module) {
                ((struct lysc_node *)node->schema)->module->ctx = ctx;
            }
        }
    }
    return node;
}

static char *copy_and_null_terminate(const uint8_t *Data, size_t Size) {
    char *str = (char *)malloc(Size + 1);
    if (!str) {
        return NULL;
    }
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    struct lys_module *module = get_module(ctx);
    struct lyd_node *parent = create_dummy_node(ctx);
    struct lyd_meta *meta = NULL;

    char *name = copy_and_null_terminate(Data, Size);
    char *val_str = copy_and_null_terminate(Data, Size);
    if (!name || !val_str) {
        goto cleanup;
    }

    uint32_t options = 0;

    // Fuzz lyd_new_meta
    if (ctx && (parent || module)) {
        lyd_new_meta(ctx, parent, module, name, val_str, options, &meta);
    }

    // Fuzz lyd_change_term
    if (parent) {
        lyd_change_term(parent, val_str);
    }

    // Fuzz lyd_new_term
    struct lyd_node *new_node = NULL;
    if (parent || module) {
        lyd_new_term(parent, module, name, val_str, options, &new_node);
    }

    // Fuzz lyd_new_path
    struct lyd_node *path_node = NULL;
    if (ctx && (parent || module)) {
        lyd_new_path(parent, ctx, name, val_str, options, &path_node);
    }

    // Fuzz lyd_change_term_canon
    if (parent) {
        lyd_change_term_canon(parent, val_str);
    }

    // Fuzz lyd_find_sibling_val
    struct lysc_node *schema = NULL;
    struct lyd_node *match = NULL;
    if (parent) {
        lyd_find_sibling_val(parent, schema, name, Size, &match);
    }

cleanup:
    if (name) free(name);
    if (val_str) free(val_str);
    if (parent) {
        if (parent->schema && ((struct lysc_node *)parent->schema)->module) {
            free(((struct lysc_node *)parent->schema)->module);
        }
        free((void *)parent->schema);
        free(parent);
    }
    if (module) free(module);
    ly_ctx_destroy(ctx);
    return 0;
}