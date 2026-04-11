#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"

static void fuzz_ly_ctx_new(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *search_dir = NULL;
    uint32_t options = 0;

    if (Size > sizeof(uint32_t)) {
        search_dir = strndup((const char *)Data, Size - sizeof(uint32_t));
        options = *(uint32_t *)(Data + Size - sizeof(uint32_t));
    }

    ly_ctx_new(search_dir, options, &ctx);

    if (ctx) {
        ly_ctx_destroy(ctx);
    }

    free(search_dir);
}

static void fuzz_ly_ctx_new_yldata(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    char *search_dir = NULL;
    int options = 0;

    if (Size > sizeof(int)) {
        search_dir = strndup((const char *)Data, Size - sizeof(int));
        options = *(int *)(Data + Size - sizeof(int));
    }

    ly_ctx_new_yldata(search_dir, tree, options, &ctx);

    if (ctx) {
        ly_ctx_destroy(ctx);
    }

    free(search_dir);
}

static void fuzz_ly_ctx_get_yanglib_data(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    char *format = NULL;

    if (Size > 0) {
        format = strndup((const char *)Data, Size);
    }

    ly_ctx_new(NULL, 0, &ctx);
    if (ctx) {
        if (format && strlen(format) > 0) {
            ly_ctx_get_yanglib_data(ctx, &root, format);
        }
        lyd_free_all(root);
        ly_ctx_destroy(ctx);
    }

    free(format);
}

static void fuzz_ly_ctx_compiled_size(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;

    ly_ctx_new(NULL, 0, &ctx);
    if (ctx) {
        ly_ctx_compiled_size(ctx);
        ly_ctx_destroy(ctx);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lyd_free_attr_single

        lyd_free_attr_single(ctx, NULL);

        // End mutation: Producer.APPEND_MUTATOR

}
}

static void fuzz_ly_ctx_new_ylmem(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *search_dir = NULL;
    char *data = NULL;
    LYD_FORMAT format = 0;
    int options = 0;

    if (Size > sizeof(LYD_FORMAT) + sizeof(int)) {
        search_dir = strndup((const char *)Data, Size - sizeof(LYD_FORMAT) - sizeof(int));
        data = strndup((const char *)Data, Size - sizeof(LYD_FORMAT) - sizeof(int));
        format = *(LYD_FORMAT *)(Data + Size - sizeof(LYD_FORMAT) - sizeof(int));
        options = *(int *)(Data + Size - sizeof(int));
    }

    ly_ctx_new_ylmem(search_dir, data, format, options, &ctx);

    if (ctx) {
        ly_ctx_destroy(ctx);
    }

    free(search_dir);
    free(data);
}

static void fuzz_lyd_parse_data_mem(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    char *data = NULL;
    LYD_FORMAT format = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;

    if (Size > sizeof(LYD_FORMAT) + 2 * sizeof(uint32_t)) {
        data = strndup((const char *)Data, Size - sizeof(LYD_FORMAT) - 2 * sizeof(uint32_t));
        format = *(LYD_FORMAT *)(Data + Size - sizeof(LYD_FORMAT) - 2 * sizeof(uint32_t));
        parse_options = *(uint32_t *)(Data + Size - 2 * sizeof(uint32_t));
        validate_options = *(uint32_t *)(Data + Size - sizeof(uint32_t));
    }

    ly_ctx_new(NULL, 0, &ctx);
    if (ctx) {
        lyd_parse_data_mem(ctx, data, format, parse_options, validate_options, &tree);
        lyd_free_all(tree);
        ly_ctx_destroy(ctx);
    }

    free(data);
}

int LLVMFuzzerTestOneInput_549(const uint8_t *Data, size_t Size) {
    fuzz_ly_ctx_new(Data, Size);
    fuzz_ly_ctx_new_yldata(Data, Size);
    fuzz_ly_ctx_get_yanglib_data(Data, Size);
    fuzz_ly_ctx_compiled_size(Data, Size);
    fuzz_ly_ctx_new_ylmem(Data, Size);
    fuzz_lyd_parse_data_mem(Data, Size);

    return 0;
}