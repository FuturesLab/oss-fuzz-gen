// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// lys_parse_mem at tree_schema.c:2872:1 in parser_schema.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_new_meta at tree_data_new.c:789:1 in tree_data.h
// lyd_dup_meta_single at tree_data.c:2617:1 in tree_data.h
// lyd_change_meta at tree_data_new.c:1224:1 in tree_data.h
// lyd_compare_meta at tree_data.c:1892:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
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
        return NULL;
    }
    return ctx;
}

static struct lys_module *create_module(struct ly_ctx *ctx) {
    const char *module_data = "module dummy {namespace \"urn:dummy\";prefix d;}";
    struct lys_module *module = NULL;
    if (lys_parse_mem(ctx, module_data, LYS_IN_YANG, &module) != LY_SUCCESS) {
        return NULL;
    }
    return module;
}

static struct lyd_node *create_parent_node(struct ly_ctx *ctx) {
    struct lyd_node *parent = NULL;
    const char *data = "{\"d:dummy\":{}}";
    if (lyd_parse_data_mem(ctx, data, LYD_JSON, LYD_PARSE_ONLY, 0, &parent) != LY_SUCCESS) {
        return NULL;
    }
    return parent;
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 3) {
        return 0;
    }

    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    struct lys_module *module = create_module(ctx);
    if (!module) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    struct lyd_node *parent = create_parent_node(ctx);
    if (!parent) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    char *name = strndup((const char *)Data, Size / 3);
    char *val_str = strndup((const char *)Data + Size / 3, Size / 3);
    uint32_t options = *(uint32_t *)(Data + 2 * (Size / 3));

    struct lyd_meta *meta = NULL;
    lyd_new_meta(ctx, parent, module, name, val_str, options, &meta);

    struct lyd_meta *dup_meta = NULL;
    lyd_dup_meta_single(meta, parent, &dup_meta);

    lyd_change_meta(meta, val_str);

    lyd_compare_meta(meta, dup_meta);

    lyd_free_meta_single(meta);
    lyd_free_meta_single(dup_meta);

    free(name);
    free(val_str);
    lyd_free_tree(parent);
    ly_ctx_destroy(ctx);

    return 0;
}