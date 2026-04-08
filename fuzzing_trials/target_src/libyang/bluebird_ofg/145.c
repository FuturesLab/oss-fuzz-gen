#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    void *compiled_pattern = NULL;
    LY_ERR err;

    // Initialize the context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ly_ctx_new
    err = ly_ctx_new(NULL, -1, &ctx);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the input data is null-terminated
    char *pattern = (char *)malloc(size + 1);
    if (!pattern) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(pattern, data, size);
    pattern[size] = '\0';

    // Call the function-under-test
    err = ly_pattern_compile(ctx, pattern, &compiled_pattern);

    // Clean up
    free(pattern);
    if (compiled_pattern) {
        free(compiled_pattern);
    }
    ly_ctx_destroy(ctx);

    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lys_parse_mem

    LY_ERR ret_lys_parse_mem_uelhq = lys_parse_mem(ctx, (const char *)"r", 0, NULL);

    // End mutation: Producer.APPEND_MUTATOR

return 0;
}