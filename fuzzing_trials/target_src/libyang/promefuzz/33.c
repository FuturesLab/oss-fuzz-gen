// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_load_module at context.c:239:1 in context.h
// ly_ctx_unset_searchdir_last at context.c:227:1 in context.h
// ly_ctx_set_searchdir at context.c:85:1 in context.h
// ly_ctx_compiled_print at context.c:1418:1 in context.h
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"

static struct ly_ctx* create_context(const char* search_dir, uint32_t options) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(search_dir, options, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static void destroy_context(struct ly_ctx *ctx) {
    if (ctx) {
        // Assuming a function ly_ctx_destroy exists for cleanup
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a context
    struct ly_ctx *ctx = create_context(NULL, 0);
    if (!ctx) {
        return 0;
    }

    // Fuzz ly_ctx_load_module
    {
        // Ensure the data is null-terminated
        char *name = (char *)malloc(Size + 1);
        if (!name) {
            destroy_context(ctx);
            return 0;
        }
        memcpy(name, Data, Size);
        name[Size] = '\0';
        const char *revision = NULL;
        const char *features[] = {NULL};
        ly_ctx_load_module(ctx, name, revision, features);
        free(name);
    }

    // Fuzz ly_ctx_unset_searchdir_last
    {
        uint32_t count = Data[0];
        ly_ctx_unset_searchdir_last(ctx, count);
    }

    // Fuzz ly_ctx_set_searchdir
    {
        // Ensure the data is null-terminated
        char *search_dir = (char *)malloc(Size + 1);
        if (!search_dir) {
            destroy_context(ctx);
            return 0;
        }
        memcpy(search_dir, Data, Size);
        search_dir[Size] = '\0';
        ly_ctx_set_searchdir(ctx, search_dir);
        free(search_dir);
    }

    // Fuzz ly_ctx_compiled_print
    {
        void *mem = malloc(1024);
        if (mem) {
            void *mem_end = NULL;
            ly_ctx_compiled_print(ctx, mem, &mem_end);
            free(mem);
        }
    }

    // Cleanup
    destroy_context(ctx);

    return 0;
}