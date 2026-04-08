// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_load_module at context.c:239:1 in context.h
// ly_ctx_unset_searchdir_last at context.c:227:1 in context.h
// ly_ctx_set_searchdir at context.c:85:1 in context.h
// ly_ctx_compile at context.c:593:1 in context.h
// ly_ctx_compiled_print at context.c:1418:1 in context.h
// ly_ctx_new_printed at context.c:1461:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"

static struct ly_ctx *initialize_context() {
    // Create a new context
    struct ly_ctx *ctx = NULL;
    LY_ERR err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize context
    struct ly_ctx *ctx = initialize_context();
    if (!ctx) {
        return 0;
    }

    // Ensure the input data is null-terminated for string operations
    char *name = (char *)malloc(Size + 1);
    if (!name) {
        cleanup_context(ctx);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    // Fuzz ly_ctx_load_module
    const char *revision = NULL;
    const char *features[] = {NULL};
    struct lys_module *module = ly_ctx_load_module(ctx, name, revision, features);

    // Fuzz ly_ctx_unset_searchdir_last
    uint32_t count = Data[0] % 10; // Arbitrary count for fuzzing
    ly_ctx_unset_searchdir_last(ctx, count);

    // Fuzz ly_ctx_set_searchdir
    ly_ctx_set_searchdir(ctx, name);

    // Fuzz ly_ctx_compile
    ly_ctx_compile(ctx);

    // Fuzz ly_ctx_compiled_print
    char mem[1024]; // Arbitrary memory size for fuzzing
    void *mem_end = NULL;
    ly_ctx_compiled_print(ctx, mem, &mem_end);

    // Fuzz ly_ctx_new_printed only if the memory is valid
    if (module) {
        struct ly_ctx *new_ctx = NULL;
        ly_ctx_new_printed(mem, &new_ctx);
        cleanup_context(new_ctx);
    }

    // Cleanup
    free(name);
    cleanup_context(ctx);

    return 0;
}