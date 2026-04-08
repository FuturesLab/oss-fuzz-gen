// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_validate_module_final at validation.c:2229:1 in parser_data.h
// lyd_validate_module at validation.c:2217:1 in parser_data.h
// lyd_compare_single at tree_data.c:1868:1 in tree_data.h
// lyd_validate_all at validation.c:2202:1 in parser_data.h
// lyd_value_validate at tree_data_common.c:601:1 in tree_data.h
// lyd_validate_op at validation.c:2438:1 in parser_data.h
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

static struct lyd_node *create_dummy_node() {
    struct lyd_node *node = malloc(sizeof(struct lyd_node));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(struct lyd_node));
    return node;
}

static struct lys_module *create_dummy_module() {
    struct lys_module *module = malloc(sizeof(struct lys_module));
    if (!module) {
        return NULL;
    }
    memset(module, 0, sizeof(struct lys_module));
    return module;
}

static const struct lysc_node *create_dummy_schema_node() {
    struct lysc_node *schema = malloc(sizeof(struct lysc_node));
    if (!schema) {
        return NULL;
    }
    memset(schema, 0, sizeof(struct lysc_node));
    return schema;
}

int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct lyd_node *tree = create_dummy_node();
    struct lys_module *module = create_dummy_module();
    const struct lysc_node *schema_node = create_dummy_schema_node();
    const char *string_value = (const char *)Data;
    uint32_t validation_options = 0;
    struct lyd_node *diff = NULL;
    const struct lysc_type *realtype = NULL;
    const char *canonical = NULL;
    struct ly_ctx *ctx = NULL;
    enum lyd_type data_type = LYD_TYPE_DATA_YANG;

    if (!tree || !module || !schema_node) {
        goto cleanup;
    }

    // Fuzz lyd_validate_module_final
    lyd_validate_module_final(tree, module, validation_options);

    // Fuzz lyd_validate_module
    lyd_validate_module(&tree, module, validation_options, &diff);

    // Fuzz lyd_value_validate
    lyd_value_validate(schema_node, string_value, Size, tree, &realtype, &canonical);

    // Fuzz lyd_validate_op
    lyd_validate_op(tree, tree, data_type, &diff);

    // Fuzz lyd_compare_single
    lyd_compare_single(tree, tree, 0);

    // Fuzz lyd_validate_all
    lyd_validate_all(&tree, ctx, validation_options, &diff);

cleanup:
    free(tree);
    free(module);
    free((void *)schema_node);
    return 0;
}