#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "/src/libyang/src/context.h"

static void test_ly_ctx_new(const char *search_dir, uint32_t options) {
    struct ly_ctx *ctx = NULL;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ly_ctx_new
    if (ly_ctx_new((const char *)"w", options, &ctx) == LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ly_ctx_new_ylmem
    if (ly_ctx_new_ylmem(NULL, data, format, options, &ctx) == LY_SUCCESS) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

int LLVMFuzzerTestOneInput_550(const uint8_t *Data, size_t Size) {
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