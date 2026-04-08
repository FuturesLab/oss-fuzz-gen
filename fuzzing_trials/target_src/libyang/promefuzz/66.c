// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_change_meta at tree_data_new.c:1224:1 in tree_data.h
// lyd_dup_meta_single at tree_data.c:2617:1 in tree_data.h
// lyd_free_meta_single at tree_data_free.c:75:1 in tree_data.h
// lyd_compare_meta at tree_data.c:1892:1 in tree_data.h
// lyd_free_meta_siblings at tree_data_free.c:81:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tree_data.h"

static struct lyd_node *create_dummy_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    node->hash = 0;
    node->flags = 0;
    node->schema = NULL;
    node->parent = NULL;
    node->next = NULL;
    node->prev = node;
    node->meta = NULL;
    node->priv = NULL;
    return node;
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    struct lyd_node *node = create_dummy_node();
    struct lyd_meta *meta = NULL;
    struct lyd_meta *dup_meta = NULL;
    LY_ERR ret;

    if (!node) {
        return 0;
    }

    // Assuming a function exists to create or retrieve a dummy metadata
    // Since struct lyd_meta is incomplete, we can't directly create it
    // meta = get_dummy_metadata();

    // Fuzzing lyd_change_meta
    char *val_str = (char *)malloc(Size + 1);
    if (val_str) {
        memcpy(val_str, Data, Size);
        val_str[Size] = '\0';
        lyd_change_meta(meta, val_str);
        free(val_str);
    }

    // Fuzzing lyd_dup_meta_single
    lyd_dup_meta_single(meta, node, &dup_meta);
    if (dup_meta) {
        lyd_free_meta_single(dup_meta);
    }

    // Fuzzing lyd_compare_meta
    lyd_compare_meta(meta, meta);

    // Fuzzing lyd_free_meta_siblings
    lyd_free_meta_siblings(meta);

    // Clean up
    if (node) {
        free(node);
    }

    return 0;
}