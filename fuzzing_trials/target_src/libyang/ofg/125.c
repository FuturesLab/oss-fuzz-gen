#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;
    char *searchdir = NULL;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for the search directory string and copy data into it
    searchdir = (char *)malloc(size + 1);
    if (searchdir == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(searchdir, data, size);
    searchdir[size] = '\0';

    // Call the function-under-test
    ly_ctx_set_searchdir(ctx, searchdir);

    // Clean up
    free(searchdir);
    ly_ctx_destroy(ctx);

    return 0;
}