#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

#define LY_SUCCESS 0
#define LY_ERR 1

static struct lys_module dummy_module = {
    .name = "dummy_module",
    .ns = "urn:dummy",
    .prefix = "dm"
};

static struct lysc_node dummy_schema_node = {
    .module = &dummy_module
};

static struct lyd_node* create_dummy_lyd_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    node->schema = &dummy_schema_node;
    node->next = node->prev = node;
    node->parent = NULL;
    node->meta = NULL;
    return node;
}

static void free_dummy_lyd_node(struct lyd_node *node) {
    if (node) {
        free(node);
    }
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    // Create dummy nodes
    struct lyd_node *sibling = create_dummy_lyd_node();
    struct lyd_node *node = create_dummy_lyd_node();
    struct lyd_node *first = NULL;

    if (!sibling || !node) {
        free_dummy_lyd_node(sibling);
        free_dummy_lyd_node(node);
        return 0;
    }

    // Ensure sibling has a valid previous pointer
    sibling->prev = sibling;

    // Fuzz lyd_insert_after
    lyd_insert_after(sibling, node);

    // Fuzz lyd_insert_before
    lyd_insert_before(sibling, node);

    // Fuzz lyd_insert_sibling
    lyd_insert_sibling(NULL, node, &first);  // Use NULL for sibling to handle start of list case

    // Fuzz lyd_insert_child
    lyd_insert_child(sibling, node);

    // Clean up
    free_dummy_lyd_node(sibling);
    free_dummy_lyd_node(node);

    return 0;
}