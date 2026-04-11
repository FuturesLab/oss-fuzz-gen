// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_load_module at context.c:239:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_internal_modules_count at context.c:1124:1 in context.h
// ly_ctx_get_modules_hash at context.c:763:1 in context.h
// ly_ctx_get_change_count at context.c:755:1 in context.h
// ly_ctx_get_module_implemented at context.c:1009:1 in context.h
// ly_ctx_get_module_iter at context.c:860:1 in context.h
// ly_ctx_get_options at context.c:618:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "context.h"

static struct ly_ctx *create_context(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        ly_ctx_destroy(ctx);
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    if (ly_ctx_load_module(ctx, "./dummy_file", NULL, NULL) == NULL) {
        ly_ctx_destroy(ctx);
        return NULL;
    }

    return ctx;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    struct ly_ctx *ctx = create_context(Data, Size);
    if (!ctx) {
        return 0;
    }

    // Test ly_ctx_internal_modules_count
    uint32_t internal_modules_count = ly_ctx_internal_modules_count(ctx);

    // Test ly_ctx_get_modules_hash
    uint32_t modules_hash = ly_ctx_get_modules_hash(ctx);

    // Test ly_ctx_get_change_count
    uint16_t change_count = ly_ctx_get_change_count(ctx);

    // Test ly_ctx_get_module_implemented
    struct lys_module *module = ly_ctx_get_module_implemented(ctx, (const char *)Data);

    // Test ly_ctx_get_module_iter
    uint32_t index = 0;
    while ((module = ly_ctx_get_module_iter(ctx, &index)) != NULL) {
        // Iterate over all modules
    }

    // Test ly_ctx_get_options
    uint32_t options = ly_ctx_get_options(ctx);

    // Cleanup
    ly_ctx_destroy(ctx);
    return 0;
}