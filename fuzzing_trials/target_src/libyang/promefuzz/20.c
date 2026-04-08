// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// lyd_parse_data_mem at tree_data.c:210:1 in parser_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_new_path at tree_data_new.c:1777:1 in tree_data.h
// lyd_parse_opaq_error at tree_data_common.c:859:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new at context.c:278:1 in context.h
// lyd_new_opaq at tree_data_new.c:878:1 in tree_data.h
// lyd_new_opaq2 at tree_data_new.c:909:1 in tree_data.h
// lyd_find_sibling_opaq_next at tree_data.c:3388:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser_data.h"
#include "tree_data.h"
#include "libyang.h"  // Include the libyang header for function declarations

static const char *generate_string(const uint8_t **Data, size_t *Size, size_t max_len) {
    if (*Size < 1) {
        return NULL;
    }

    size_t len = **Data % max_len;
    (*Data)++;
    (*Size)--;

    if (*Size < len) {
        return NULL;
    }

    char *str = (char *)malloc(len + 1);
    if (!str) {
        return NULL;
    }

    memcpy(str, *Data, len);
    str[len] = '\0';

    *Data += len;
    *Size -= len;

    return str;
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    const char *name = generate_string(&Data, &Size, 20);
    const char *value = generate_string(&Data, &Size, 20);
    const char *prefix = generate_string(&Data, &Size, 10);
    const char *module_name = generate_string(&Data, &Size, 20);
    const char *module_ns = generate_string(&Data, &Size, 20);
    const char *path = generate_string(&Data, &Size, 50);

    struct lyd_node *parent = NULL;
    struct lyd_node *node = NULL;

    lyd_new_opaq(parent, ctx, name, value, prefix, module_name, &node);
    lyd_new_opaq2(parent, ctx, name, value, prefix, module_ns, &node);

    struct lyd_node *match = NULL;
    lyd_find_sibling_opaq_next(parent, name, &match);

    const char *data = generate_string(&Data, &Size, 100);
    if (Size < 1) {
        free((void *)name);
        free((void *)value);
        free((void *)prefix);
        free((void *)module_name);
        free((void *)module_ns);
        free((void *)path);
        free((void *)data);
        ly_ctx_destroy(ctx);
        return 0;
    }
    LYD_FORMAT format = (LYD_FORMAT)(*Data % 3);
    Data++;
    Size--;

    if (Size < 1) {
        free((void *)name);
        free((void *)value);
        free((void *)prefix);
        free((void *)module_name);
        free((void *)module_ns);
        free((void *)path);
        free((void *)data);
        ly_ctx_destroy(ctx);
        return 0;
    }
    uint32_t parse_options = *Data;
    Data++;
    Size--;

    if (Size < 1) {
        free((void *)name);
        free((void *)value);
        free((void *)prefix);
        free((void *)module_name);
        free((void *)module_ns);
        free((void *)path);
        free((void *)data);
        ly_ctx_destroy(ctx);
        return 0;
    }
    uint32_t validate_options = *Data;
    Data++;
    Size--;

    struct lyd_node *tree = NULL;
    lyd_parse_data_mem(ctx, data, format, parse_options, validate_options, &tree);

    if (Size < 1) {
        free((void *)name);
        free((void *)value);
        free((void *)prefix);
        free((void *)module_name);
        free((void *)module_ns);
        free((void *)path);
        free((void *)data);
        lyd_free_all(tree);
        ly_ctx_destroy(ctx);
        return 0;
    }
    uint32_t options = *Data;
    Data++;
    Size--;

    lyd_new_path(parent, ctx, path, value, options, &node);

    lyd_parse_opaq_error(node);

    free((void *)name);
    free((void *)value);
    free((void *)prefix);
    free((void *)module_name);
    free((void *)module_ns);
    free((void *)path);
    free((void *)data);

    lyd_free_all(tree);
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}