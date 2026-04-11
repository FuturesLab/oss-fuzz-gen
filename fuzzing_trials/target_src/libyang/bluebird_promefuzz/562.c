#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/tree_data.h"

static void fuzz_ly_pattern_compile(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *pattern = strndup((const char *)Data, Size);
    void *pat_comp = NULL;

    if (pattern) {
        LY_ERR result = ly_pattern_compile(ctx, pattern, &pat_comp);
        if (result == LY_SUCCESS) {
            ly_pattern_free(pat_comp);
        }
        free(pattern);
    }
}

static void fuzz_lyd_value_validate(const uint8_t *Data, size_t Size) {
    struct lysc_node *schema = NULL;
    const char *value = (const char *)Data;
    uint32_t value_len = (uint32_t)Size;
    const struct lyd_node *ctx_node = NULL;
    const struct lysc_type *realtype = NULL;
    const char *canonical = NULL;

    lyd_value_validate(schema, value, value_len, ctx_node, &realtype, &canonical);
}

static void fuzz_lyd_change_term(const uint8_t *Data, size_t Size) {
    struct lyd_node *term = NULL;
    char *val_str = strndup((const char *)Data, Size);

    if (val_str) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_change_term with lyd_change_term_canon
        lyd_change_term_canon(term, val_str);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        free(val_str);
    }
}

static void fuzz_ly_pattern_match(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *pattern = strndup((const char *)Data, Size / 2);
    char *string = strndup((const char *)(Data + Size / 2), Size / 2);
    void *pat_comp = NULL;

    if (pattern && string) {
        ly_pattern_match(ctx, pattern, string, (uint32_t)strlen(string), &pat_comp);
        if (pat_comp) {
            ly_pattern_free(pat_comp);
        }
        free(pattern);
        free(string);
    }
}

static void fuzz_lyd_parse_data_path(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    const char *path = "./dummy_file";
    FILE *file = fopen(path, "wb");
    if (!file) {
        return;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    LYD_FORMAT format = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;
    struct lyd_node *tree = NULL;

    lyd_parse_data_path(ctx, path, format, parse_options, validate_options, &tree);
}

int LLVMFuzzerTestOneInput_562(const uint8_t *Data, size_t Size) {
    fuzz_ly_pattern_compile(Data, Size);
    fuzz_lyd_value_validate(Data, Size);
    fuzz_lyd_change_term(Data, Size);
    fuzz_ly_pattern_match(Data, Size);
    fuzz_lyd_parse_data_path(Data, Size);

    return 0;
}