#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = "/tmp/searchdir";
    LY_ERR err;

    // Create a new context to ensure ctx is not NULL
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the search directory is set initially
    err = ly_ctx_set_searchdir(ctx, search_dir);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to set search directory\n");
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Prepare a string from the fuzzing data
    char *fuzzed_dir = (char *)malloc(size + 1);
    if (fuzzed_dir == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    memcpy(fuzzed_dir, data, size);
    fuzzed_dir[size] = '\0';

    // Call the function under test
    ly_ctx_unset_searchdir(ctx, fuzzed_dir);

    // Clean up
    free(fuzzed_dir);
    ly_ctx_destroy(ctx);

    return 0;
}