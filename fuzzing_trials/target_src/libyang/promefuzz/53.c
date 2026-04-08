// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_get_value at tree_data.h:1163:1 in tree_data.h
// lyd_parse_data_path at tree_data.c:238:1 in parser_data.h
// lyd_free_tree at tree_data_free.c:265:1 in tree_data.h
// lyd_child at tree_data.h:1032:1 in tree_data.h
// lyd_node_schema at tree_data_common.c:1010:1 in tree_data.h
// lyd_find_xpath at tree_data.c:3424:1 in tree_data.h
// lyd_child_any at tree_data.h:1062:1 in tree_data.h
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser_data.h"
#include "tree_data.h"
#include "libyang.h"

static void fuzz_lyd_get_value(const struct lyd_node *node) {
    const char *value = lyd_get_value(node);
    if (value) {
        // Perform operations on the value if needed
    }
}

static void fuzz_lyd_parse_data_path(struct ly_ctx *ctx, const uint8_t *Data, size_t Size) {
    char path[] = "./dummy_file";
    FILE *file = fopen(path, "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    struct lyd_node *tree = NULL;
    LY_ERR ret = lyd_parse_data_path(ctx, path, 0, 0, 0, &tree);
    if (ret == LY_SUCCESS && tree) {
        // Perform operations on the tree if needed
        lyd_free_tree(tree);
    }
}

static void fuzz_lyd_child(const struct lyd_node *node) {
    struct lyd_node *child = lyd_child(node);
    if (child) {
        // Perform operations on the child if needed
    }
}

static void fuzz_lyd_node_schema(const struct lyd_node *node) {
    const struct lysc_node *schema = lyd_node_schema(node);
    if (schema) {
        // Perform operations on the schema if needed
    }
}

static void fuzz_lyd_find_xpath(const struct lyd_node *ctx_node, const uint8_t *Data, size_t Size) {
    char xpath[Size + 1];
    memcpy(xpath, Data, Size);
    xpath[Size] = '\0';

    struct ly_set *set = NULL;
    LY_ERR ret = lyd_find_xpath(ctx_node, xpath, &set);
    if (ret == LY_SUCCESS && set) {
        // Perform operations on the set if needed
        ly_set_free(set, NULL);
    }
}

static void fuzz_lyd_child_any(const struct lyd_node *node) {
    struct lyd_node *child = lyd_child_any(node);
    if (child) {
        // Perform operations on the child if needed
    }
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    struct lyd_node *node = NULL;
    fuzz_lyd_get_value(node);
    fuzz_lyd_parse_data_path(ctx, Data, Size);
    fuzz_lyd_child(node);
    fuzz_lyd_node_schema(node);
    fuzz_lyd_find_xpath(node, Data, Size);
    fuzz_lyd_child_any(node);

    ly_ctx_destroy(ctx);
    return 0;
}