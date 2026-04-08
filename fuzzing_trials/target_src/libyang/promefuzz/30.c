// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_set_searchdir at context.c:85:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_unset_searchdir at context.c:181:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new_yldata at context.c:497:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new_ylpath at context.c:449:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// lyd_parse_data_path at tree_data.c:238:1 in parser_data.h
// lyd_free_all at tree_data_free.c:311:1 in tree_data.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_get_searchdirs at context.c:159:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "context.h"
#include "parser_data.h"

static void fuzz_ly_ctx_new_yldata(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    const char *search_dir = ".";
    int options = 0;

    // Attempt to create a new context with the fuzzing data
    ly_ctx_new_yldata(search_dir, tree, options, &ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_ly_ctx_new_ylpath(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = ".";
    const char *path = "./dummy_file";
    LYD_FORMAT format = 0;
    int options = 0;

    // Write fuzzing data to a dummy file
    FILE *file = fopen(path, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Attempt to create a new context with the file path
    ly_ctx_new_ylpath(search_dir, path, format, options, &ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_lyd_parse_data_path(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *tree = NULL;
    const char *path = "./dummy_file";
    LYD_FORMAT format = 0;
    uint32_t parse_options = 0;
    uint32_t validate_options = 0;

    // Write fuzzing data to a dummy file
    FILE *file = fopen(path, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Attempt to parse the data from the file
    lyd_parse_data_path(ctx, path, format, parse_options, validate_options, &tree);

    // Clean up
    if (tree) {
        lyd_free_all(tree);
    }
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_ly_ctx_get_searchdirs(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    const char * const *searchdirs;

    // Create a new context
    ly_ctx_new(NULL, 0, &ctx);

    // Get the search directories
    searchdirs = ly_ctx_get_searchdirs(ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

static void fuzz_ly_ctx_set_searchdir(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *search_dir = malloc(Size + 1);
    if (!search_dir) {
        return;
    }
    memcpy(search_dir, Data, Size);
    search_dir[Size] = '\0';

    // Create a new context
    ly_ctx_new(NULL, 0, &ctx);

    // Set the search directory
    ly_ctx_set_searchdir(ctx, search_dir);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    free(search_dir);
}

static void fuzz_ly_ctx_unset_searchdir(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    char *search_dir = malloc(Size + 1);
    if (!search_dir) {
        return;
    }
    memcpy(search_dir, Data, Size);
    search_dir[Size] = '\0';

    // Create a new context
    ly_ctx_new(NULL, 0, &ctx);

    // Unset the search directory
    ly_ctx_unset_searchdir(ctx, search_dir);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    free(search_dir);
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    fuzz_ly_ctx_new_yldata(Data, Size);
    fuzz_ly_ctx_new_ylpath(Data, Size);
    fuzz_lyd_parse_data_path(Data, Size);
    fuzz_ly_ctx_get_searchdirs(Data, Size);
    fuzz_ly_ctx_set_searchdir(Data, Size);
    fuzz_ly_ctx_unset_searchdir(Data, Size);

    return 0;
}