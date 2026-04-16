#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "libyang.h"
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/tree_data.h"

static void prepare_context(struct ly_ctx **ctx) {
    if (ly_ctx_new(NULL, 0, ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context.\n");
        exit(EXIT_FAILURE);
    }
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_lyd_validate_all(struct lyd_node **tree, struct ly_ctx *ctx) {
    struct lyd_node *diff = NULL;
    uint32_t val_opts = 0;
    LY_ERR ret = lyd_validate_all(tree, ctx, val_opts, &diff);
    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_validate_all failed.\n");
    }
    lyd_free_all(diff);
}

static void fuzz_lyd_parse_data(struct ly_ctx *ctx, const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    struct ly_in *in;
    LY_ERR ret;

    // Ensure the input data is null-terminated
    char *data_copy = (char *)malloc(Size + 1);
    if (!data_copy) {
        return;
    }
    memcpy(data_copy, Data, Size);
    data_copy[Size] = '\0';

    if (ly_in_new_memory(data_copy, &in) != LY_SUCCESS) {
        free(data_copy);
        return;
    }

    ret = lyd_parse_data(ctx, NULL, in, LYD_XML, 0, 0, &tree);
    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_parse_data failed.\n");
    }

    lyd_free_all(tree);
    ly_in_free(in, 0);
    free(data_copy);
}

static void fuzz_lyd_new_path2(struct ly_ctx *ctx) {
    struct lyd_node *parent = NULL, *new_node = NULL;
    const char *path = "/example-module:container/list[key='value']";
    LY_ERR ret;

    ret = lyd_new_path2(NULL, ctx, path, NULL, 0, 0, 0, &parent, &new_node);
    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_path2 failed.\n");
    }

    lyd_free_tree(parent);
}

static void fuzz_lyd_validate_ext(struct lyd_node **ext_tree, struct lysc_ext_instance *ext) {
    struct lyd_node *diff = NULL;
    uint32_t val_opts = 0;
    LY_ERR ret = lyd_validate_ext(ext_tree, ext, val_opts, &diff);
    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_validate_ext failed.\n");
    }
    lyd_free_all(diff);
}

static void fuzz_lyd_new_implicit_all(struct lyd_node **tree, struct ly_ctx *ctx) {
    struct lyd_node *diff = NULL;
    uint32_t implicit_options = 0;

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_new_implicit_all with lyd_validate_all
    LY_ERR ret = lyd_validate_all(tree, ctx, implicit_options, &diff);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_implicit_all failed.\n");
    }
    lyd_free_all(diff);
}

static void fuzz_lyd_dup_single_to_ctx(struct lyd_node *node, struct ly_ctx *ctx) {
    struct lyd_node *dup = NULL;
    LY_ERR ret = lyd_dup_single_to_ctx(node, ctx, NULL, 0, &dup);
    if (ret != LY_SUCCESS) {
        fprintf(stderr, "lyd_dup_single_to_ctx failed.\n");
    }
    lyd_free_tree(dup);
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    struct lysc_ext_instance ext = {0};

    prepare_context(&ctx);

    fuzz_lyd_validate_all(&tree, ctx);
    fuzz_lyd_parse_data(ctx, Data, Size);
    fuzz_lyd_new_path2(ctx);
    fuzz_lyd_validate_ext(&tree, &ext);
    fuzz_lyd_new_implicit_all(&tree, ctx);
    fuzz_lyd_dup_single_to_ctx(tree, ctx);

    lyd_free_tree(tree);
    cleanup_context(ctx);

    return 0;
}