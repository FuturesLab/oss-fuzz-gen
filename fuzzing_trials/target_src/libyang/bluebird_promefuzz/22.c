#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h"

static void dummy_cleanup(struct lyd_node *node, struct ly_ctx *ctx) {
    if (node) {
        lyd_free_tree(node);
    }
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL, *dup = NULL, *parent = NULL;
    struct ly_set *set = NULL;
    LY_ERR ret;

    // Initialize context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    // Create a dummy node
    if (lyd_new_path(NULL, ctx, "/test-module:container", NULL, 0, &node) != LY_SUCCESS) {
        dummy_cleanup(node, ctx);
        return 0;
    }

    // Fuzzing lyd_dup_single_to_ctx
    ret = lyd_dup_single_to_ctx(node, ctx, parent, 0, &dup);
    if (ret == LY_SUCCESS) {
        lyd_free_tree(dup);
    }

    // Fuzzing lyd_compare_single
    ret = lyd_compare_single(node, node, 0);

    // Fuzzing lyd_dup_siblings
    ret = lyd_dup_siblings(node, parent, 0, &dup);
    if (ret == LY_SUCCESS) {
        lyd_free_tree(dup);
    }

    // Fuzzing lyd_diff_siblings
    struct lyd_node *diff = NULL;
    ret = lyd_diff_siblings(node, node, 0, &diff);
    if (ret == LY_SUCCESS && diff) {
        lyd_free_tree(diff);
    }

    // Fuzzing lyd_find_sibling_dup_inst_set
    ret = lyd_find_sibling_dup_inst_set(node, node, &set);
    if (ret == LY_SUCCESS && set) {
        ly_set_free(set, NULL);
    }

    // Fuzzing lyd_compare_siblings
    ret = lyd_compare_siblings(node, node, 0);

    // Cleanup
    dummy_cleanup(node, ctx);

    return 0;
}