#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Prepare namespace and revision strings, ensuring they are null-terminated
    char *namespace = malloc(size + 1);
    if (!namespace) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(namespace, data, size);
    namespace[size] = '\0';

    // Use a fixed revision for simplicity
    const char *revision = "2023-10-01";

    // Call the function under test
    module = ly_ctx_get_module_ns(ctx, namespace, revision);

    // Clean up
    free(namespace);
    ly_ctx_destroy(ctx);

    return 0;
}