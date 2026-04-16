// This fuzz driver is generated for library libyang, aiming to fuzz the following functions:
// ly_ctx_new at context.c:278:1 in context.h
// ly_ctx_set_searchdir at context.c:85:1 in context.h
// ly_ctx_load_module at context.c:239:1 in context.h
// ly_ctx_unset_searchdir_last at context.c:227:1 in context.h
// ly_ctx_compiled_print at context.c:1418:1 in context.h
// ly_ctx_new_printed at context.c:1461:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
// ly_ctx_destroy at context.c:1503:1 in context.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "context.h"

static void initialize_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + 1) {
        return 0;
    }

    initialize_dummy_file(Data, Size);

    struct ly_ctx *ctx = NULL;
    struct ly_ctx *printed_ctx = NULL;
    struct lys_module *module = NULL;
    void *mem = malloc(1024);
    void *mem_end = NULL;

    // Extract a valid uint32_t value from Data
    uint32_t options = *((uint32_t *)Data);
    const char *search_dir = (const char *)(Data + sizeof(uint32_t));

    // Ensure the search directory is null-terminated
    char *safe_search_dir = strndup(search_dir, Size - sizeof(uint32_t));

    // Fuzz ly_ctx_new
    ly_ctx_new(safe_search_dir, options % 2, &ctx);

    if (ctx) {
        // Fuzz ly_ctx_set_searchdir
        ly_ctx_set_searchdir(ctx, safe_search_dir);

        // Fuzz ly_ctx_load_module
        module = ly_ctx_load_module(ctx, safe_search_dir, NULL, NULL);

        // Fuzz ly_ctx_unset_searchdir_last
        ly_ctx_unset_searchdir_last(ctx, options % 2);

        // Fuzz ly_ctx_compiled_print
        ly_ctx_compiled_print(ctx, mem, &mem_end);

        // Fuzz ly_ctx_new_printed
        ly_ctx_new_printed(mem, &printed_ctx);

        // Clean up
        if (printed_ctx) {
            ly_ctx_destroy(printed_ctx);
        }

        ly_ctx_destroy(ctx);
    }

    free(mem);
    free(safe_search_dir);
    return 0;
}