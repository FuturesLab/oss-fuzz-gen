#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const struct lys_module *module = NULL;
    const struct lysp_submodule *submodule = NULL;
    char *module_name = NULL;
    char *submodule_name = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the data is null-terminated for string usage
    module_name = malloc(size + 1);
    if (!module_name) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(module_name, data, size);
    module_name[size] = '\0';

    // Load a module into the context for testing purposes
    err = lys_parse_mem(ctx, "module test {namespace urn:test;prefix t;}", LYS_IN_YANG, (struct lys_module **)&module);
    if (err != LY_SUCCESS) {
        free(module_name);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Use the same data for submodule name, or create a new one if necessary
    submodule_name = strdup(module_name);
    if (!submodule_name) {
        free(module_name);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    submodule = ly_ctx_get_submodule2_latest(module, submodule_name);

    // Clean up
    free(module_name);
    free(submodule_name);
    ly_ctx_destroy(ctx);

    return 0;
}