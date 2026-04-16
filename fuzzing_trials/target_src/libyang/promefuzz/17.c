// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_internal_modules_count at context.c:1124:1 in context.h
// ly_ctx_is_printed at context.c:1493:1 in context.h
// ly_ctx_get_modules_hash at context.c:763:1 in context.h
// ly_ctx_get_module_implemented at context.c:1009:1 in context.h
// ly_ctx_free_parsed at context.c:1360:1 in context.h
// ly_ctx_get_options at context.c:618:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "context.h"

static struct ly_ctx *create_dummy_context() {
    // Create a dummy context using a library function
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return NULL;
    }
    return ctx;
}

static void free_dummy_context(struct ly_ctx *ctx) {
    // Free the dummy context using a library function
    ly_ctx_destroy(ctx);
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct ly_ctx *ctx = create_dummy_context();
    if (!ctx) {
        return 0;
    }

    // Test ly_ctx_internal_modules_count
    uint32_t internal_modules_count = ly_ctx_internal_modules_count(ctx);
    (void)internal_modules_count;  // Suppress unused variable warning

    // Test ly_ctx_is_printed
    ly_bool is_printed = ly_ctx_is_printed(ctx);
    (void)is_printed;  // Suppress unused variable warning

    // Test ly_ctx_get_modules_hash
    uint32_t modules_hash = ly_ctx_get_modules_hash(ctx);
    (void)modules_hash;  // Suppress unused variable warning

    // Test ly_ctx_get_module_implemented
    const char *module_name = (const char *)Data;
    struct lys_module *module = ly_ctx_get_module_implemented(ctx, module_name);
    (void)module;  // Suppress unused variable warning

    // Test ly_ctx_free_parsed
    ly_ctx_free_parsed(ctx);

    // Test ly_ctx_get_options
    uint32_t options = ly_ctx_get_options(ctx);
    (void)options;  // Suppress unused variable warning

    free_dummy_context(ctx);

    return 0;
}