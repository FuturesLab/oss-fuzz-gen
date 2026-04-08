#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/parser_schema.h"

static void fuzz_ly_pattern_compile(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    void *pat_comp = NULL;
    char *pattern = NULL;

    if (Size > 0) {
        pattern = strndup((const char *)Data, Size);
        if (pattern) {
            LY_ERR result = ly_pattern_compile(ctx, pattern, &pat_comp);
            if (result == LY_SUCCESS) {
                ly_pattern_free(pat_comp);
            }
            free(pattern);
        }
    }
}

static void fuzz_ly_pattern_match(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    void *pat_comp = NULL;
    char *pattern = NULL;
    char *string = NULL;

    if (Size > 1) {
        size_t half = Size / 2;
        pattern = strndup((const char *)Data, half);
        string = strndup((const char *)Data + half, Size - half);

        if (pattern && string) {
            LY_ERR result = ly_pattern_compile(ctx, pattern, &pat_comp);
            if (result == LY_SUCCESS) {
                ly_pattern_match(ctx, pattern, string, strlen(string), &pat_comp);

                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_pattern_match to ly_ctx_set_ext_data_clb

                ly_ext_data_clb ret_ly_ctx_set_ext_data_clb_daezo = ly_ctx_set_ext_data_clb(NULL, NULL, pat_comp);

                // End mutation: Producer.APPEND_MUTATOR

                ly_pattern_free(pat_comp);
            }
            free(pattern);
            free(string);
        }
    }
}

static void fuzz_ly_ctx_get_yanglib_data(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    char *content_id_format = NULL;

    if (Size > 0) {
        content_id_format = strndup((const char *)Data, Size);
        if (content_id_format) {
            ly_ctx_get_yanglib_data(ctx, &root, content_id_format);
            free(content_id_format);
        }
    }
}

static void fuzz_lys_parse_path(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LYS_INFORMAT format = 0; // Assume some default format
    FILE *file = fopen("./dummy_file", "wb");

    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        lys_parse_path(ctx, "./dummy_file", format, &module);
    }
}

static void fuzz_lyd_parse_data_path(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    LYD_FORMAT format = 0; // Assume some default format
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    FILE *file = fopen("./dummy_file", "wb");

    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        lyd_parse_data_path(ctx, "./dummy_file", format, parse_options, validate_options, &tree);
    }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_parse_data_path to lyd_compare_single

        LY_ERR ret_lyd_compare_single_twexq = lyd_compare_single(tree, NULL, 0);

        // End mutation: Producer.APPEND_MUTATOR

}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    fuzz_ly_pattern_compile(Data, Size);
    fuzz_ly_pattern_match(Data, Size);
    fuzz_ly_ctx_get_yanglib_data(Data, Size);
    fuzz_lys_parse_path(Data, Size);
    fuzz_lyd_parse_data_path(Data, Size);
    return 0;
}