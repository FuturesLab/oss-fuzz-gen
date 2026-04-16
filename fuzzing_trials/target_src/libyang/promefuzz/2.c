// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_set_options at context.c:626:1 in context.h
// ly_ctx_compile at context.c:593:1 in context.h
// ly_ctx_set_module_imp_clb at context.c:816:1 in context.h
// ly_ctx_unset_options at context.c:704:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_new_ylmem at context.c:473:1 in context.h
// ly_ctx_set_options at context.c:626:1 in context.h
// ly_ctx_compile at context.c:593:1 in context.h
// ly_ctx_set_module_imp_clb at context.c:816:1 in context.h
// ly_ctx_unset_options at context.c:704:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"

static void test_ly_ctx_new(const char *search_dir, uint32_t options) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(search_dir, options, &ctx) == LY_SUCCESS) {
        // Test ly_ctx_set_options
        ly_ctx_set_options(ctx, options);

        // Test ly_ctx_compile
        ly_ctx_compile(ctx);

        // Test ly_ctx_set_module_imp_clb with a dummy callback
        ly_ctx_set_module_imp_clb(ctx, NULL, NULL);

        // Test ly_ctx_unset_options
        ly_ctx_unset_options(ctx, options);

        // Cleanup
        ly_ctx_destroy(ctx);
    }
}

static void test_ly_ctx_new_ylmem(const char *search_dir, const char *data, LYD_FORMAT format, int options) {
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new_ylmem(search_dir, data, format, options, &ctx) == LY_SUCCESS) {
        // Test ly_ctx_set_options
        ly_ctx_set_options(ctx, options);

        // Test ly_ctx_compile
        ly_ctx_compile(ctx);

        // Test ly_ctx_set_module_imp_clb with a dummy callback
        ly_ctx_set_module_imp_clb(ctx, NULL, NULL);

        // Test ly_ctx_unset_options
        ly_ctx_unset_options(ctx, options);

        // Cleanup
        ly_ctx_destroy(ctx);
    }
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    // Use the first byte as options
    uint32_t options = Data[0];

    // Use the next byte as format
    LYD_FORMAT format = (LYD_FORMAT)Data[1];

    // Use the rest as search_dir and data
    char *search_dir = strndup((const char *)Data + 2, (Size - 2) / 2);
    char *data = strndup((const char *)Data + 2 + (Size - 2) / 2, (Size - 2) / 2);

    // Test ly_ctx_new
    test_ly_ctx_new(search_dir, options);

    // Test ly_ctx_new_ylmem
    test_ly_ctx_new_ylmem(search_dir, data, format, options);

    free(search_dir);
    free(data);

    return 0;
}