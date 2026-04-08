// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_insert_after at tree_data.c:1164:1 in tree_data.h
// lyd_insert_before at tree_data.c:1140:1 in tree_data.h
// lyd_insert_sibling at tree_data.c:1114:1 in tree_data.h
// lyd_insert_child at tree_data.c:1095:1 in tree_data.h
// lyd_diff_apply_all at diff.c:1971:1 in tree_data.h
// lyd_diff_tree at diff.c:1429:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tree_data.h"

static struct lys_module *initialize_module() {
    // Dummy module initialization
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    return module;
}

static struct lysc_node *initialize_schema_node(struct lys_module *module, uint16_t nodetype) {
    struct lysc_node *schema = (struct lysc_node *)malloc(sizeof(struct lysc_node));
    if (!schema) return NULL;
    schema->nodetype = nodetype;
    schema->module = module;
    return schema;
}

static struct lyd_node *initialize_lyd_node(struct lysc_node *schema) {
    if (!schema) return NULL;
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) return NULL;
    node->schema = schema;
    node->prev = node;  // Circular reference for single node
    node->next = NULL;
    node->parent = NULL;
    return node;
}

static void cleanup_node(struct lyd_node *node) {
    if (node) {
        free((void *)node->schema);
        free(node);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    struct lys_module *module = initialize_module();
    if (!module) return 0;

    // Initialize schema nodes
    struct lysc_node *schema1 = initialize_schema_node(module, LYS_LIST);
    struct lysc_node *schema2 = initialize_schema_node(module, LYS_LIST);

    // Initialize lyd_nodes
    struct lyd_node *sibling = initialize_lyd_node(schema1);
    struct lyd_node *node = initialize_lyd_node(schema2);

    if (!sibling || !node) {
        cleanup_node(sibling);
        cleanup_node(node);
        free(module);
        return 0;
    }

    // Fuzzing the lyd_insert_after function
    if (sibling->schema && node->schema) {
        lyd_insert_after(sibling, node);
    }

    // Fuzzing the lyd_insert_before function
    if (sibling->schema && node->schema) {
        lyd_insert_before(sibling, node);
    }

    // Fuzzing the lyd_insert_sibling function
    struct lyd_node *first = NULL;
    if (sibling->schema && node->schema) {
        lyd_insert_sibling(sibling, node, &first);
    }

    // Fuzzing the lyd_insert_child function
    if (sibling->schema && node->schema) {
        lyd_insert_child(sibling, node);
    }

    // Fuzzing the lyd_diff_apply_all function
    struct lyd_node *data_tree = sibling;
    struct lyd_node *diff_tree = node;
    if (data_tree && diff_tree) {
        lyd_diff_apply_all(&data_tree, diff_tree);
    }

    // Fuzzing the lyd_diff_tree function
    struct lyd_node *diff = NULL;
    if (sibling->schema && node->schema) {
        lyd_diff_tree(sibling, node, 0, &diff);
    }

    // Cleanup
    cleanup_node(sibling);
    cleanup_node(node);
    cleanup_node(diff);
    free(module);

    return 0;
}