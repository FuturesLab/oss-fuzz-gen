#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/libyang/src/context.h"

static struct ly_ctx *initialize_context() {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != 0) {
        return NULL;
    }
    return ctx;
}

static void cleanup_context(struct ly_ctx *ctx) {
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = initialize_context();
    if (!ctx) {
        return 0;
    }

    // Prepare input strings
    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) {
        cleanup_context(ctx);
        return 0;
    }
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Use a portion of the input data as a namespace and revision
    const char *namespace = input_str;
    const char *revision = Size > 1 ? &input_str[1] : NULL;

    // Fuzz ly_ctx_get_module_ns
    struct lys_module *mod_ns = ly_ctx_get_module_ns(ctx, namespace, revision);

    // Fuzz ly_ctx_get_module_latest_ns
    struct lys_module *mod_latest_ns = ly_ctx_get_module_latest_ns(ctx, namespace);

    // Fuzz ly_ctx_load_module
    const char *features[] = {NULL};
    struct lys_module *mod_load = ly_ctx_load_module(ctx, namespace, revision, features);

    // Fuzz ly_ctx_get_module
    struct lys_module *mod_get = ly_ctx_get_module(ctx, namespace, revision);

    // Fuzz ly_ctx_get_module_implemented
    struct lys_module *mod_impl = ly_ctx_get_module_implemented(ctx, namespace);

    // Fuzz ly_ctx_get_module_implemented_ns
    struct lys_module *mod_impl_ns = ly_ctx_get_module_implemented_ns(ctx, namespace);

    // Cleanup
    free(input_str);
    cleanup_context(ctx);

    return 0;
}