#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
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

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
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