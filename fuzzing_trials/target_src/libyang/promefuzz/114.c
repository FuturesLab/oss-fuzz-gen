// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_insert_after at tree_data.c:1164:1 in tree_data.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_data.h"
#include "tree_data.h"

static struct lyd_node *create_lyd_node(const char *name, struct lysc_node *schema) {
    struct lyd_node *node = (struct lyd_node *)malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(struct lyd_node));
    node->schema = schema;
    return node;
}

static struct lysc_node *create_lysc_node(const char *name, struct lys_module *module) {
    struct lysc_node *schema = (struct lysc_node *)malloc(sizeof(struct lysc_node));
    if (!schema) {
        return NULL;
    }
    memset(schema, 0, sizeof(struct lysc_node));
    schema->module = module;
    schema->name = name;
    return schema;
}

static struct lys_module *create_lys_module(const char *name) {
    struct lys_module *module = (struct lys_module *)malloc(sizeof(struct lys_module));
    if (!module) {
        return NULL;
    }
    memset(module, 0, sizeof(struct lys_module));
    module->name = name;
    return module;
}

int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare the environment
    struct lys_module *module = create_lys_module("test_module");
    struct lysc_node *schema1 = create_lysc_node("node1", module);
    struct lysc_node *schema2 = create_lysc_node("node2", module);

    struct lyd_node *sibling = create_lyd_node("sibling", schema1);
    struct lyd_node *node = create_lyd_node("node", schema2);

    if (!sibling || !node || !schema1 || !schema2 || !module) {
        goto cleanup;
    }

    // Fuzzing the lyd_insert_after function
    LY_ERR result = lyd_insert_after(sibling, node);

    // Cleanup
cleanup:
    free(sibling);
    free(node);
    free(schema1);
    free(schema2);
    free(module);

    return 0;
}