#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Ensure data is null-terminated
    char *ylpath = (char *)malloc(size + 1);
    if (!ylpath) {
        return 0;
    }
    memcpy(ylpath, data, size);
    ylpath[size] = '\0';

    // Use a fixed path and format for testing
    const char *search_dir = "/tmp";
    LYD_FORMAT format = LYD_JSON;
    int options = 0;

    // Call the function-under-test
    err = ly_ctx_new_ylpath(search_dir, ylpath, format, options, &ctx);

    // Clean up
    if (ctx) {
        ly_ctx_destroy(ctx);
    }
    free(ylpath);

    return 0;
}