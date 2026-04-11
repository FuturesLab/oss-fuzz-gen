#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "/src/libyang/src/tree_data.h"

static struct lyd_node *create_dummy_node() {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(struct lyd_node));
    node->prev = node;  // Ensure prev is never NULL
    struct lysc_node *schema = (struct lysc_node *)malloc(sizeof(struct lysc_node)); // Allocate schema
    if (!schema) {
        free(node);
        return NULL;
    }
    memset(schema, 0, sizeof(struct lysc_node));
    schema->module = (struct lys_module *)malloc(sizeof(struct lys_module)); // Allocate module
    if (!schema->module) {
        free(schema);
        free(node);
        return NULL;
    }
    memset(schema->module, 0, sizeof(struct lys_module));
    node->schema = schema;
    return node;
}

static struct lys_module *create_dummy_module() {
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    if (!module) {
        return NULL;
    }
    memset(module, 0, sizeof(struct lys_module));
    return module;
}

static void free_dummy_node(struct lyd_node *node) {
    if (node) {
        if (node->schema) {
            if (node->schema->module) {
                free((void *)node->schema->module);
            }
            free((void *)node->schema);
        }
        free(node);
    }
}

static void free_dummy_module(struct lys_module *module) {
    if (module) {
        free(module);
    }
}

int LLVMFuzzerTestOneInput_519(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct lyd_node *node = create_dummy_node();
    if (!node) {
        return 0;
    }

    struct lys_module *module = create_dummy_module();
    if (!module) {
        free_dummy_node(node);
        return 0;
    }

    // Fuzzing lyd_child_any
    const struct lyd_node *child_any = lyd_child_any(node);

    // Fuzzing lyd_child
    const struct lyd_node *child = lyd_child(node);

    // Fuzzing lyd_first_sibling
    struct lyd_node *first_sibling = lyd_first_sibling(node);

    // Fuzzing lyd_insert_after
    struct lyd_node *new_node = create_dummy_node();
    if (new_node) {
        LY_ERR err = lyd_insert_after(node, new_node);
        if (err != LY_SUCCESS) {
            free_dummy_node(new_node);
        }
    }

    // Fuzzing lyd_insert_child
    struct lyd_node *child_node = create_dummy_node();
    if (child_node) {
        LY_ERR err = lyd_insert_child(node, child_node);
        if (err != LY_SUCCESS) {
            free_dummy_node(child_node);
        }
    }

    // Fuzzing lyd_new_implicit_module
    struct lyd_node *tree = NULL;
    struct lyd_node *diff = NULL;
    uint32_t implicit_options = (uint32_t)Data[0];
    LY_ERR err = lyd_new_implicit_module(&tree, module, implicit_options, &diff);
    if (err == LY_SUCCESS) {
        free_dummy_node(tree);
        free_dummy_node(diff);
    }

    // Cleanup
    free_dummy_node(node);
    free_dummy_module(module);

    return 0;
}