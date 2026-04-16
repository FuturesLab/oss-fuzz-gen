#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_schema.h"

static struct ly_ctx *create_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx)) {
        return NULL;
    }
    return ctx;
}

static void destroy_context(struct ly_ctx *ctx) {
    ly_ctx_destroy(ctx);
}

static void test_ly_ctx_get_searchdirs(struct ly_ctx *ctx) {
    const char * const *dirs = ly_ctx_get_searchdirs(ctx);
    if (dirs) {
        for (int i = 0; dirs[i]; ++i) {
            printf("Searchdir: %s\n", dirs[i]);
        }
    }
}

static void test_ly_ctx_get_module_implemented(struct ly_ctx *ctx, const char *name) {
    struct lys_module *mod = ly_ctx_get_module_implemented(ctx, name);
    if (mod) {
        printf("Module implemented: %s\n", mod->name);
    }
}

static void test_ly_ctx_set_searchdir(struct ly_ctx *ctx, const char *search_dir) {
    if (ly_ctx_set_searchdir(ctx, search_dir) != LY_SUCCESS) {
        fprintf(stderr, "Failed to set searchdir: %s\n", search_dir);
    }
}

static void test_lys_parse_path(struct ly_ctx *ctx, const char *path, LYS_INFORMAT format) {
    struct lys_module *mod = NULL;
    if (lys_parse_path(ctx, path, format, &mod) != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse path: %s\n", path);
    } else if (mod) {
        printf("Parsed module: %s\n", mod->name);
    }
}

static void test_lys_search_localfile(const char * const *searchpaths, ly_bool cwd, const char *name) {
    char *localfile = NULL;
    LYS_INFORMAT format;
    if (lys_search_localfile(searchpaths, cwd, name, NULL, &localfile, &format) == LY_SUCCESS && localfile) {
        printf("Found schema file: %s\n", localfile);
        free(localfile);
    }
}

static void test_ly_ctx_load_module(struct ly_ctx *ctx, const char *name, const char *revision, const char **features) {
    struct lys_module *mod = ly_ctx_load_module(ctx, name, revision, features);
    if (mod) {
        printf("Loaded module: %s\n", mod->name);
    }
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = create_context();
    if (!ctx) {
        return 0;
    }

    char dummy_file[] = "./dummy_file";
    FILE *file = fopen(dummy_file, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    test_ly_ctx_get_searchdirs(ctx);
    test_ly_ctx_set_searchdir(ctx, "/tmp");
    test_ly_ctx_get_module_implemented(ctx, "example-module");
    test_lys_parse_path(ctx, dummy_file, 0);
    test_lys_search_localfile(NULL, 1, "example-schema");
    test_ly_ctx_load_module(ctx, "example-module", NULL, NULL);

    destroy_context(ctx);
    return 0;
}