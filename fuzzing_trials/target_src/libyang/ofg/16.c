#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *searchdir = (char *)malloc(size + 1);
    if (!searchdir) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(searchdir, data, size);
    searchdir[size] = '\0';

    // Set the search directory first to ensure the unset operation has an effect
    err = ly_ctx_set_searchdir(ctx, searchdir);
    if (err == LY_SUCCESS) {
        // Call the function-under-test
        ly_ctx_unset_searchdir(ctx, searchdir);
    }

    // Clean up
    free(searchdir);
    ly_ctx_destroy(ctx);

    return 0;
}