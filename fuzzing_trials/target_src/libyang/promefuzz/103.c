// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// lys_parse_mem at tree_schema.c:2872:1 in parser_schema.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_new_meta at tree_data_new.c:789:1 in tree_data.h
// lyd_find_meta at tree_data.c:3138:1 in tree_data.h
// lyd_compare_meta at tree_data.c:1892:1 in tree_data.h
// lyd_meta_is_internal at tree_data_common.c:1053:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h"

static struct ly_ctx *create_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context.\n");
        return NULL;
    }
    return ctx;
}

static struct lys_module *create_module(struct ly_ctx *ctx) {
    if (!ctx) {
        return NULL;
    }
    const char *module_data = "module dummy { namespace \"urn:dummy\"; prefix d; }";
    struct lys_module *module = NULL;
    if (lys_parse_mem(ctx, module_data, LYS_IN_YANG, &module) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create module.\n");
        return NULL;
    }
    return module;
}

static struct lyd_node *create_parent_node(struct ly_ctx *ctx, const struct lys_module *module) {
    if (!ctx || !module) {
        return NULL;
    }
    struct lyd_node *parent = NULL;
    if (lyd_new_path(NULL, ctx, "/dummy:parent", NULL, 0, &parent) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create parent node.\n");
        return NULL;
    }
    return parent;
}

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    struct lys_module *module = create_module(ctx);
    if (!module) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    struct lyd_node *parent = create_parent_node(ctx, module);
    if (!parent) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    char *name = strndup((const char *)Data, Size);
    char *val_str = strndup((const char *)Data, Size);

    struct lyd_meta *meta = NULL;
    LY_ERR err = lyd_new_meta(ctx, parent, module, name, val_str, 0, &meta);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_meta failed.\n");
    }

    if (meta) {
        struct lyd_meta *found_meta = lyd_find_meta(meta, module, name);
        if (found_meta) {
            lyd_compare_meta(meta, found_meta);
        }

        lyd_meta_is_internal(meta);

        lyd_free_meta_single(meta);
    }

    free(name);
    free(val_str);
    lyd_free_tree(parent);
    ly_ctx_destroy(ctx);

    return 0;
}