// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_diff_merge_tree at diff.c:3018:1 in tree_data.h
// lyd_diff_reverse_all at diff.c:3473:1 in tree_data.h
// lyd_diff_apply_module at diff.c:1946:1 in tree_data.h
// lyd_diff_merge_all at diff.c:3034:1 in tree_data.h
// lyd_diff_merge_module at diff.c:2995:1 in tree_data.h
// lyd_diff_tree at diff.c:1429:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree_data.h"

#define DUMMY_FILE_PATH "./dummy_file"

static struct lyd_node *create_dummy_lyd_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (node) {
        memset(node, 0, sizeof(struct lyd_node));
        node->schema = (struct lysc_node *)malloc(sizeof(struct lysc_node));
        if (node->schema) {
            memset((void *)node->schema, 0, sizeof(struct lysc_node));
        }
    }
    return node;
}

static void free_lyd_node(struct lyd_node *node) {
    if (node) {
        if (node->schema) {
            free((void *)node->schema);
        }
        free(node);
    }
}

static LY_ERR dummy_diff_callback(const struct lyd_node *diff_node, struct lyd_node *data_node, void *cb_data) {
    (void)diff_node;
    (void)data_node;
    (void)cb_data;
    return LY_SUCCESS;
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint16_t)) {
        return 0;
    }

    // Prepare dummy data
    struct lyd_node *diff_first = create_dummy_lyd_node();
    struct lyd_node *diff_parent = create_dummy_lyd_node();
    struct lyd_node *src_sibling = create_dummy_lyd_node();
    struct lyd_node *data = create_dummy_lyd_node();
    struct lys_module *mod = NULL;
    struct lyd_node *src_diff = create_dummy_lyd_node();
    struct lyd_node *first = create_dummy_lyd_node();
    struct lyd_node *second = create_dummy_lyd_node();
    struct lyd_node *diff = NULL;
    uint16_t options = *(uint16_t *)Data;

    // Dummy file operation
    FILE *file = fopen(DUMMY_FILE_PATH, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Fuzzing the API functions
    lyd_diff_merge_tree(&diff_first, diff_parent, src_sibling, dummy_diff_callback, NULL, options);
    lyd_diff_reverse_all(src_diff, &diff);
    lyd_diff_apply_module(&data, diff, mod, dummy_diff_callback, NULL);
    lyd_diff_merge_all(&diff_first, src_diff, options);
    lyd_diff_merge_module(&diff_first, src_diff, mod, dummy_diff_callback, NULL, options);
    lyd_diff_tree(first, second, options, &diff);

    // Cleanup
    free_lyd_node(diff_first);
    free_lyd_node(diff_parent);
    free_lyd_node(src_sibling);
    free_lyd_node(src_diff);
    free_lyd_node(first);
    free_lyd_node(second);
    free_lyd_node(data);
    free_lyd_node(diff);

    return 0;
}