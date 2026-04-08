// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_merge_module at tree_data.c:2856:1 in tree_data.h
// lyd_node_module at tree_data_common.c:336:1 in tree_data.h
// lyd_new_any at tree_data_new.c:749:1 in tree_data.h
// lyd_merge_tree at tree_data.c:2844:1 in tree_data.h
// lyd_node_schema at tree_data_common.c:1010:1 in tree_data.h
// lyd_owner_module at tree_data_common.c:299:1 in tree_data.h
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
    if (node) {
        memset(node, 0, sizeof(struct lyd_node));
        node->prev = node; // Initialize prev to point to itself to avoid invalid memory access
        node->next = NULL;
        node->parent = NULL;
        node->schema = NULL;
        node->meta = NULL;
        node->priv = NULL;
    }
    return node;
}

static struct lys_module *create_dummy_lys_module() {
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    if (module) {
        memset(module, 0, sizeof(struct lys_module));
    }
    return module;
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    struct lyd_node *target = create_dummy_lyd_node();
    struct lyd_node *source = create_dummy_lyd_node();
    struct lys_module *mod = create_dummy_lys_module();

    if (!target || !source || !mod) {
        free(target);
        free(source);
        free(mod);
        return 0;
    }

    // Fuzz lyd_merge_module
    uint16_t merge_options = Data[0];
    lyd_merge_module(&target, source, mod, NULL, NULL, merge_options);

    // Fuzz lyd_node_module
    const struct lys_module *retrieved_mod = lyd_node_module(source);

    // Fuzz lyd_new_any
    struct lyd_node *new_node = NULL;
    const char *name = "dummy_name";
    const char *value = "dummy_value";
    uint32_t hints = 0;
    uint32_t options = 0;
    lyd_new_any(target, mod, name, NULL, value, hints, options, &new_node);

    // Fuzz lyd_merge_tree
    uint16_t tree_options = Data[0];
    lyd_merge_tree(&target, source, tree_options);

    // Fuzz lyd_node_schema
    const struct lysc_node *schema_node = lyd_node_schema(source);

    // Fuzz lyd_owner_module
    const struct lys_module *owner_mod = lyd_owner_module(source);

    // Cleanup
    free(target);
    free(source);
    free(mod);
    free(new_node);

    return 0;
}