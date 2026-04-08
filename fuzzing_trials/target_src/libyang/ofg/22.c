#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = "/some/search/dir"; // Example search directory
    const char *ylmem = (const char *)data; // Use the fuzzer data as ylmem input
    LYD_FORMAT format = LYD_JSON; // Example format
    int options = 0; // Example options
    LY_ERR err;

    // Ensure the data is null-terminated for string operations
    char *ylmem_copy = (char *)malloc(size + 1);
    if (ylmem_copy == NULL) {
        return 0;
    }
    memcpy(ylmem_copy, data, size);
    ylmem_copy[size] = '\0';

    // Call the function-under-test
    err = ly_ctx_new_ylmem(search_dir, ylmem_copy, format, options, &ctx);

    // Clean up
    ly_ctx_destroy(ctx);
    free(ylmem_copy);

    return 0;
}