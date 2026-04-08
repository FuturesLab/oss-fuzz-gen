#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // Include for uint8_t
#include "libyang.h"

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Allocate memory for the module string
    char *module_data = (char *)malloc(size + 1);
    if (module_data == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Copy the fuzzing data into the module string and null-terminate it
    memcpy(module_data, data, size);
    module_data[size] = '\0';

    // Parse the module from the input data
    err = lys_parse_mem(ctx, module_data, LYS_IN_YANG, &module);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse module\n");
    }

    // Clean up
    free(module_data);
    ly_ctx_destroy(ctx);

    return 0;
}