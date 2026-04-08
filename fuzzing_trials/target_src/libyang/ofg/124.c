#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for search_dir and copy data into it
    search_dir = (char *)malloc(size + 1);
    if (search_dir == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy((char *)search_dir, data, size);
    ((char *)search_dir)[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    ly_ctx_set_searchdir(ctx, search_dir);

    // Clean up
    free((char *)search_dir);
    ly_ctx_destroy(ctx);

    return 0;
}