#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    char *name = NULL;
    char *revision = NULL;

    // Initialize the context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for name and revision strings
    name = (char *)malloc(size + 1);
    revision = (char *)malloc(size + 1);

    if (!name || !revision) {
        fprintf(stderr, "Memory allocation failed\n");
        ly_ctx_destroy(ctx);
        free(name);
        free(revision);
        return 0;
    }

    // Copy data into name and revision, ensuring null-termination
    memcpy(name, data, size);
    name[size] = '\0';
    memcpy(revision, data, size);
    revision[size] = '\0';

    // Call the function under test
    module = ly_ctx_get_module(ctx, name, revision);

    // Clean up
    ly_ctx_destroy(ctx);
    free(name);
    free(revision);

    return 0;
}