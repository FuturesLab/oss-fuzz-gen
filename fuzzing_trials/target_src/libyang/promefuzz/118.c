// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_diff_apply_all at diff.c:1971:1 in tree_data.h
// lyd_diff_reverse_all at diff.c:3473:1 in tree_data.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
// lyd_diff_siblings at diff.c:1435:1 in tree_data.h
// lyd_dup_single at tree_data.c:2510:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h"
#include "parser_data.h"
#include "tree_data.h"

static struct ly_ctx *create_context(void) {
    struct ly_ctx *ctx = NULL;
    // Initialize context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static struct lyd_node *create_node(struct ly_ctx *ctx, const char *path, const char *value) {
    struct lyd_node *node = NULL;
    lyd_new_path(NULL, ctx, path, value, 0, &node);
    return node;
}

int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    // Create a null-terminated string from Data
    char *value = (char *)malloc(Size + 1);
    if (!value) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(value, Data, Size);
    value[Size] = '\0';

    // Create dummy data and diff nodes
    struct lyd_node *data = create_node(ctx, "/example-module:container", NULL);
    struct lyd_node *diff = create_node(ctx, "/example-module:container", NULL);
    struct lyd_node *reversed_diff = NULL;
    struct lyd_node *dup_node = NULL;
    struct lyd_node *diff_siblings = NULL;
    struct lys_module *module = NULL;
    struct lyd_node *validate_diff = NULL;

    // Fuzzing target functions
    lyd_diff_apply_all(&data, diff);
    lyd_diff_reverse_all(diff, &reversed_diff);
    lyd_validate_module(&data, module, 0, &validate_diff);
    lyd_new_path(data, ctx, "/example-module:leaf", value, 0, NULL);
    lyd_diff_siblings(data, diff, 0, &diff_siblings);
    lyd_dup_single(data, NULL, 0, &dup_node);

    // Cleanup
    free(value);
    lyd_free_all(data);
    lyd_free_all(diff);
    lyd_free_all(reversed_diff);
    lyd_free_all(dup_node);
    lyd_free_all(diff_siblings);
    lyd_free_all(validate_diff);
    ly_ctx_destroy(ctx);

    return 0;
}