// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_find_sibling_opaq_next at tree_data.c:3388:1 in tree_data.h
// lyd_any_value_str at tree_data_common.c:981:1 in tree_data.h
// lyd_unlink_siblings at tree_data.c:1266:1 in tree_data.h
// lyd_find_sibling_first at tree_data.c:3182:1 in tree_data.h
// lyd_find_target at tree_data.c:3735:1 in tree_data.h
// lyd_diff_tree at diff.c:1429:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tree_data.h"

static struct lyd_node *create_dummy_lyd_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) return NULL;
    memset(node, 0, sizeof(struct lyd_node));
    node->prev = node;
    // Allocate memory for the schema node and cast away the constness for initialization
    struct lysc_node *schema = (struct lysc_node *)malloc(sizeof(struct lysc_node));
    if (!schema) {
        free(node);
        return NULL;
    }
    memset(schema, 0, sizeof(struct lysc_node));
    schema->name = "dummy_name"; // Assign a dummy name
    node->schema = schema; // Assign the schema
    return node;
}

static void free_dummy_lyd_node(struct lyd_node *node) {
    if (node) {
        free((void *)node->schema);
        free(node);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // lyd_find_sibling_opaq_next
    struct lyd_node *first = create_dummy_lyd_node();
    struct lyd_node *match = NULL;
    const char *name = (const char *)Data;
    lyd_find_sibling_opaq_next(first, name, &match);
    free_dummy_lyd_node(first);

    // lyd_any_value_str
    struct lyd_node *any = create_dummy_lyd_node();
    LYD_FORMAT format = (LYD_FORMAT)(Data[0] % 3); // assume 3 formats
    char *value_str = NULL;
    lyd_any_value_str(any, format, &value_str);
    free(value_str);
    free_dummy_lyd_node(any);

    // lyd_unlink_siblings
    struct lyd_node *node_to_unlink = create_dummy_lyd_node();
    lyd_unlink_siblings(node_to_unlink);
    free_dummy_lyd_node(node_to_unlink);

    // lyd_find_sibling_first
    struct lyd_node *siblings = create_dummy_lyd_node();
    struct lyd_node *target = create_dummy_lyd_node();
    struct lyd_node *first_match = NULL;
    lyd_find_sibling_first(siblings, target, &first_match);
    free_dummy_lyd_node(siblings);
    free_dummy_lyd_node(target);

    // lyd_find_target
    // Since ly_path is an incomplete type, we cannot allocate it directly.
    struct lyd_node *tree = create_dummy_lyd_node();
    struct lyd_node *found_match = NULL;
    lyd_find_target(NULL, tree, &found_match); // Passing NULL for path
    free_dummy_lyd_node(tree);

    // lyd_diff_tree
    struct lyd_node *first_tree = create_dummy_lyd_node();
    struct lyd_node *second_tree = create_dummy_lyd_node();
    struct lyd_node *diff = NULL;
    uint16_t options = 0;
    lyd_diff_tree(first_tree, second_tree, options, &diff);
    free_dummy_lyd_node(first_tree);
    free_dummy_lyd_node(second_tree);
    free_dummy_lyd_node(diff);

    return 0;
}