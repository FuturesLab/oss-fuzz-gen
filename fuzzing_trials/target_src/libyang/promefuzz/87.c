// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_insert_after at tree_data.c:1164:1 in tree_data.h
// lyd_insert_before at tree_data.c:1140:1 in tree_data.h
// lyd_merge_siblings at tree_data.c:2850:1 in tree_data.h
// lyd_insert_sibling at tree_data.c:1114:1 in tree_data.h
// lyd_unlink_tree at tree_data.c:1293:1 in tree_data.h
// lyd_unlink_siblings at tree_data.c:1266:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "tree_data.h"

static struct lys_module dummy_module = {
    .name = "dummy",
    .ns = "urn:dummy",
    .prefix = "dm",
};

static struct lysc_node dummy_schema_node = {
    .nodetype = 0,
    .module = &dummy_module,
    .name = "dummy_node",
};

static struct lyd_node *create_dummy_node() {
    struct lyd_node *node = malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    node->schema = &dummy_schema_node;
    node->parent = NULL;
    node->next = node->prev = node;
    node->meta = NULL;
    node->priv = NULL;
    return node;
}

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct lyd_node *node1 = create_dummy_node();
    struct lyd_node *node2 = create_dummy_node();
    struct lyd_node *sibling = create_dummy_node();
    struct lyd_node *target = create_dummy_node();
    struct lyd_node *source = create_dummy_node();
    
    if (!node1 || !node2 || !sibling || !target || !source) {
        free(node1);
        free(node2);
        free(sibling);
        free(target);
        free(source);
        return 0;
    }

    // Fuzzing lyd_insert_after
    lyd_insert_after(sibling, node1);

    // Fuzzing lyd_insert_before
    lyd_insert_before(sibling, node2);

    // Fuzzing lyd_merge_siblings
    lyd_merge_siblings(&target, source, (uint16_t)Data[0]);

    // Fuzzing lyd_insert_sibling
    struct lyd_node *first = NULL;
    lyd_insert_sibling(sibling, node1, &first);

    // Fuzzing lyd_unlink_tree
    lyd_unlink_tree(node1);

    // Fuzzing lyd_unlink_siblings
    lyd_unlink_siblings(node2);

    // Cleanup
    free(node1);
    free(node2);
    free(sibling);
    free(target);
    free(source);

    return 0;
}