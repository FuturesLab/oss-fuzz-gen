#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include "/src/libyang/build/libyang/context.h" // Include for ly_ctx functions
#include "/src/libyang/build/libyang/parser_schema.h" // Include for lys_parse_mem

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        exit(EXIT_FAILURE);
    }

    // Ensure data is null-terminated
    char *schema_data = (char *)malloc(size + 1);
    if (!schema_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(schema_data, data, size);
    schema_data[size] = '\0';

    // Call the function-under-test
    lys_parse_mem(ctx, schema_data, LYS_IN_YANG, &module);

    // Clean up
    free(schema_data);
    ly_ctx_destroy(ctx);

    return 0;
}