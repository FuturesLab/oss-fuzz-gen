// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new_yldata at context.c:497:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_find_path at tree_data.c:3700:1 in tree_data.h
// ly_ctx_get_yanglib_data at context.c:1216:1 in context.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_find_sibling_first at tree_data.c:3182:1 in tree_data.h
// lyd_owner_module at tree_data_common.c:299:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"
#include "tree_data.h"

static void fuzz_ly_ctx_new_yldata(const uint8_t *Data, size_t Size) {
    const char *search_dir = NULL;
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    int options = 0;

    if (Size > 0) {
        search_dir = (const char *)Data;
    }

    LY_ERR ret = ly_ctx_new_yldata(search_dir, tree, options, &ctx);
    if (ret == LY_SUCCESS && ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_lyd_find_path(const uint8_t *Data, size_t Size) {
    struct lyd_node *ctx_node = NULL;
    const char *path = NULL;
    ly_bool output = 0;
    struct lyd_node *match = NULL;

    if (Size > 0) {
        path = (const char *)Data;
    }

    LY_ERR ret = lyd_find_path(ctx_node, path, output, &match);
    if (ret == LY_SUCCESS && match) {
        // Use match if needed
    }
}

static void fuzz_ly_ctx_get_yanglib_data(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    const char *content_id_format = NULL;

    if (Size > 0) {
        content_id_format = (const char *)Data;
    }

    LY_ERR ret = ly_ctx_get_yanglib_data(ctx, &root, content_id_format);
    if (ret == LY_SUCCESS && root) {
        lyd_free_all(root);
    }
}

static void fuzz_lyd_new_path(const uint8_t *Data, size_t Size) {
    struct lyd_node *parent = NULL;
    struct ly_ctx *ctx = NULL;
    const char *path = NULL;
    const char *value = NULL;
    uint32_t options = 0;
    struct lyd_node *node = NULL;

    if (Size > 0) {
        path = (const char *)Data;
    }

    LY_ERR ret = lyd_new_path(parent, ctx, path, value, options, &node);
    if (ret == LY_SUCCESS && node) {
        lyd_free_all(node);
    }
}

static void fuzz_lyd_find_sibling_first(const uint8_t *Data, size_t Size) {
    struct lyd_node *siblings = NULL;
    struct lyd_node *target = NULL;
    struct lyd_node *match = NULL;

    LY_ERR ret = lyd_find_sibling_first(siblings, target, &match);
    if (ret == LY_SUCCESS && match) {
        // Use match if needed
    }
}

static void fuzz_lyd_owner_module(const uint8_t *Data, size_t Size) {
    struct lyd_node *node = NULL;
    const struct lys_module *module = lyd_owner_module(node);
    if (module) {
        // Use module if needed
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    fuzz_ly_ctx_new_yldata(Data, Size);
    fuzz_lyd_find_path(Data, Size);
    fuzz_ly_ctx_get_yanglib_data(Data, Size);
    fuzz_lyd_new_path(Data, Size);
    fuzz_lyd_find_sibling_first(Data, Size);
    fuzz_lyd_owner_module(Data, Size);
    return 0;
}