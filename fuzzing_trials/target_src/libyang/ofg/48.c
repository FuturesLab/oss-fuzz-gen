#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const struct lys_module *module = NULL;
    char *module_name = NULL;

    // Initialize context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for module_name and copy fuzz data into it
    module_name = (char *)malloc(size + 1);
    if (!module_name) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(module_name, data, size);
    module_name[size] = '\0'; // Null-terminate the string

    // Attempt to load a module with the fuzz data
    if (lys_parse_mem(ctx, module_name, LYS_IN_YANG, (struct lys_module **)&module) != LY_SUCCESS) {
        // If parsing fails, clean up and return
        free(module_name);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    module = ly_ctx_get_module_latest(ctx, module_name);

    // Clean up
    free(module_name);
    ly_ctx_destroy(ctx);

    return 0;
}