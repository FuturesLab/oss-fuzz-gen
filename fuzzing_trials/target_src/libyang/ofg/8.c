#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    const char *name = "example-submodule";
    const char *revision = "2023-10-01";
    const struct lysp_submodule *submodule = NULL;
    char *schema = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Prepare a valid YANG module schema
    schema = (char *)malloc(size + 1);
    if (!schema) {
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