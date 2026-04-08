#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/context.h"

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *search_dir = "/tmp"; // Example search directory
    const char *ylpath = "/tmp/ylpath"; // Example ylpath
    LYD_FORMAT format = LYD_JSON; // Example format
    int options = 0; // Example options
    char *input_data = NULL;
    LY_ERR err;

    // Allocate and copy data to a null-terminated string
    input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Call the function-under-test
    err = ly_ctx_new_ylpath(search_dir, ylpath, format, options, &ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    free(input_data);

    return 0;
}