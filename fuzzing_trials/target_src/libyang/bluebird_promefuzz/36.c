#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libyang.h" // Ensure this header is included for function declarations

static void fuzz_lyd_parse_value_fragment(const uint8_t *Data, size_t Size) {
    if (Size < 5) {
        return;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return;
    }

    struct ly_in *in = NULL;
    if (ly_in_new_memory((const char *)Data, &in)) {
        ly_ctx_destroy(ctx);
        return;
    }

    const char *path = "/path/to/node";
    LYD_FORMAT format = LYD_JSON;
    uint32_t new_val_options = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;

    lyd_parse_value_fragment(ctx, path, in, format, new_val_options, parse_options, validate_options, &tree);

    lyd_free_all(tree);
    ly_in_free(in, 0);
    ly_ctx_destroy(ctx);
}

static void fuzz_lyd_parse_data_mem(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    // Ensure null-termination of input data
    char *data_copy = (char *)malloc(Size + 1);
    if (!data_copy) {
        return;
    }
    memcpy(data_copy, Data, Size);
    data_copy[Size] = '\0';

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        free(data_copy);
        return;
    }

    LYD_FORMAT format = LYD_JSON;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;

    lyd_parse_data_mem(ctx, data_copy, format, parse_options, validate_options, &tree);

    lyd_free_all(tree);
    free(data_copy);
    ly_ctx_destroy(ctx);
}

static void fuzz_lyd_new_path(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return;
    }

    struct lyd_node *parent = NULL;
    const char *path = "/path/to/node";

    // Ensure null-termination of input data
    char *value_copy = (char *)malloc(Size + 1);
    if (!value_copy) {
        ly_ctx_destroy(ctx);
        return;
    }
    memcpy(value_copy, Data, Size);
    value_copy[Size] = '\0';

    uint32_t options = 0;
    struct lyd_node *node = NULL;

    lyd_new_path(parent, ctx, path, value_copy, options, &node);

    lyd_free_all(node);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_free_all to ly_ctx_get_module_imp_clb

    ly_module_imp_clb ret_ly_ctx_get_module_imp_clb_ldoox = ly_ctx_get_module_imp_clb(NULL, (void **)&node);

    // End mutation: Producer.APPEND_MUTATOR

    free(value_copy);
    ly_ctx_destroy(ctx);
}

static void fuzz_lyd_parse_data_path(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return;
    }

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        ly_ctx_destroy(ctx);
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    LYD_FORMAT format = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;

    lyd_parse_data_path(ctx, "./dummy_file", format, parse_options, validate_options, &tree);

    lyd_free_all(tree);
    ly_ctx_destroy(ctx);
}

static void fuzz_lyd_parse_data(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return;
    }

    struct ly_in *in = NULL;
    if (ly_in_new_memory((const char *)Data, &in)) {
        ly_ctx_destroy(ctx);
        return;
    }

    LYD_FORMAT format = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of lyd_parse_data
    lyd_parse_data(ctx, NULL, in, format, 0, validate_options, &tree);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    lyd_free_all(tree);
    ly_in_free(in, 0);
    ly_ctx_destroy(ctx);
}

static void fuzz_lyd_find_path(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return;
    }

    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return;
    }

    struct lyd_node *ctx_node = NULL;
    const char *path = "/path/to/node";
    ly_bool output = 0;
    struct lyd_node *match = NULL;

    lyd_find_path(ctx_node, path, output, &match);

    ly_ctx_destroy(ctx);
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    fuzz_lyd_parse_value_fragment(Data, Size);
    fuzz_lyd_parse_data_mem(Data, Size);
    fuzz_lyd_new_path(Data, Size);
    fuzz_lyd_parse_data_path(Data, Size);
    fuzz_lyd_parse_data(Data, Size);
    fuzz_lyd_find_path(Data, Size);
    return 0;
}