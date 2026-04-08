#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/in.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/context.h"

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;  // Return early if data is null or size is zero
    }

    struct ly_ctx *ctx = NULL;
    struct ly_in *input = NULL;
    const char *features[] = {NULL};
    struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure null-termination for the input data
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        fprintf(stderr, "Memory allocation failed\n");
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize the input structure with null-terminated data
    err = ly_in_new_memory(null_terminated_data, &input);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create input memory\n");
        free(null_terminated_data);
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Call the function-under-test
    err = lys_parse(ctx, input, LYS_IN_YANG, features, &module);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to parse module\n");
    }

    // Clean up
    ly_in_free(input, 0);
    ly_ctx_destroy(ctx);
    free(null_terminated_data); // Free the memory after input is no longer needed

    return 0;
}