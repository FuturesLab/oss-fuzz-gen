// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_new_meta at tree_data_new.c:789:1 in tree_data.h
// ly_ctx_new at context.c:278:1 in context.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_change_meta at tree_data_new.c:1224:1 in tree_data.h
// lyd_dup_meta_single at tree_data.c:2617:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// lyd_compare_meta at tree_data.c:1892:1 in tree_data.h
// lyd_free_meta_siblings at tree_data_free.c:81:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree_data.h"
#include "libyang.h"

static struct lyd_meta* create_dummy_meta(struct ly_ctx *ctx, struct lyd_node *parent) {
    struct lyd_meta* meta = NULL;
    lyd_new_meta(ctx, parent, NULL, "dummy", "dummy_value", 0, &meta);
    return meta;
}

static struct lyd_node* create_dummy_node() {
    struct lyd_node* node = (struct lyd_node*)malloc(sizeof(struct lyd_node));
    if (!node) return NULL;
    node->parent = NULL;
    node->next = NULL;
    node->prev = node; // point to itself
    node->meta = NULL;
    node->schema = NULL;
    return node;
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    struct lyd_node* parent = create_dummy_node();
    struct lyd_meta* meta1 = create_dummy_meta(ctx, parent);
    struct lyd_meta* meta2 = create_dummy_meta(ctx, parent);

    if (!parent || !meta1 || !meta2) {
        free(parent);
        lyd_free_meta_single(meta1);
        lyd_free_meta_single(meta2);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Fuzz lyd_change_meta
    if (Size > 0) {
        char* val_str = (char*)malloc(Size + 1);
        if (val_str) {
            memcpy(val_str, Data, Size);
            val_str[Size] = '\0';
            lyd_change_meta(meta1, val_str);
            free(val_str);
        }
    }

    // Fuzz lyd_dup_meta_single
    struct lyd_meta* dup_meta = NULL;
    lyd_dup_meta_single(meta1, parent, &dup_meta);
    if (dup_meta) {
        lyd_free_meta_single(dup_meta);
    }

    // Fuzz lyd_compare_meta
    lyd_compare_meta(meta1, meta2);

    // Fuzz lyd_free_meta_siblings
    lyd_free_meta_siblings(meta1);

    // Fuzz lyd_free_meta_single
    lyd_free_meta_single(meta2);

    free(parent);
    ly_ctx_destroy(ctx);
    return 0;
}