#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const struct lysp_submodule *submodule;
    const char *name = "example-submodule";
    const char *revision = "2023-10-01";
    LY_ERR err;

    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a new context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Use the input data as a schema for testing purposes
    char *schema = malloc(size + 1);
    if (schema == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(schema, data, size);
    schema[size] = '\0';

    // Parse the schema to add it to the context
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Call the function-under-test
    submodule = ly_ctx_get_submodule(ctx, name, revision);

    // Clean up
    free(schema);
    ly_ctx_destroy(ctx);

    return 0;
}