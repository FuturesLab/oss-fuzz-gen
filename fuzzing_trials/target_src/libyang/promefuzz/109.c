// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_dup_single_to_ctx at tree_data.c:2522:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_validate_all at validation.c:2202:1 in parser_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_validate_ext at validation.c:2148:1 in parser_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_insert_child at tree_data.c:1095:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_new_implicit_all at tree_data_new.c:2010:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_new_implicit_tree at tree_data_new.c:1971:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser_data.h"
#include "tree_data.h"

static void fuzz_lyd_validate_all(const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    struct ly_ctx *ctx = NULL;
    struct lyd_node *diff = NULL;
    uint32_t val_opts = 0;

    if (Size >= sizeof(uint32_t)) {
        val_opts = *(uint32_t *)Data;
    }

    LY_ERR ret = lyd_validate_all(&tree, ctx, val_opts, &diff);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(diff);
    lyd_free_all(tree);
}

static void fuzz_lyd_validate_ext(const uint8_t *Data, size_t Size) {
    struct lyd_node *ext_tree = NULL;
    struct lysc_ext_instance *ext = NULL;
    struct lyd_node *diff = NULL;
    uint32_t val_opts = 0;

    if (Size >= sizeof(uint32_t)) {
        val_opts = *(uint32_t *)Data;
    }

    LY_ERR ret = lyd_validate_ext(&ext_tree, ext, val_opts, &diff);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(diff);
    lyd_free_all(ext_tree);
}

static void fuzz_lyd_insert_child(const uint8_t *Data, size_t Size) {
    struct lyd_node *parent = NULL;
    struct lyd_node *node = NULL;

    LY_ERR ret = lyd_insert_child(parent, node);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(parent);
    lyd_free_all(node);
}

static void fuzz_lyd_new_implicit_all(const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    struct ly_ctx *ctx = NULL;
    struct lyd_node *diff = NULL;
    uint32_t implicit_options = 0;

    if (Size >= sizeof(uint32_t)) {
        implicit_options = *(uint32_t *)Data;
    }

    LY_ERR ret = lyd_new_implicit_all(&tree, ctx, implicit_options, &diff);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(diff);
    lyd_free_all(tree);
}

static void fuzz_lyd_new_implicit_tree(const uint8_t *Data, size_t Size) {
    struct lyd_node *tree = NULL;
    struct lyd_node *diff = NULL;
    uint32_t implicit_options = 0;

    if (Size >= sizeof(uint32_t)) {
        implicit_options = *(uint32_t *)Data;
    }

    LY_ERR ret = lyd_new_implicit_tree(tree, implicit_options, &diff);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(diff);
    lyd_free_all(tree);
}

static void fuzz_lyd_dup_single_to_ctx(const uint8_t *Data, size_t Size) {
    const struct lyd_node *node = NULL;
    struct ly_ctx *trg_ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *dup = NULL;
    uint32_t options = 0;

    if (Size >= sizeof(uint32_t)) {
        options = *(uint32_t *)Data;
    }

    LY_ERR ret = lyd_dup_single_to_ctx(node, trg_ctx, parent, options, &dup);
    if (ret != LY_SUCCESS) {
        // Handle error if needed
    }

    // Clean up
    lyd_free_all(dup);
    lyd_free_all(parent);
}

int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    fuzz_lyd_validate_all(Data, Size);
    fuzz_lyd_validate_ext(Data, Size);
    fuzz_lyd_insert_child(Data, Size);
    fuzz_lyd_new_implicit_all(Data, Size);
    fuzz_lyd_new_implicit_tree(Data, Size);
    fuzz_lyd_dup_single_to_ctx(Data, Size);

    return 0;
}