#include <stdint.h>
#include <stdlib.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    const char *schema = "module fuzz {namespace urn:fuzz;prefix f;container c {leaf l {type string;}}}";
    LY_ERR err;

    // Create a libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Parse the schema to create a context
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Allocate memory for data and ensure it's null-terminated
    char *data_copy = (char *)malloc(size + 1);
    if (!data_copy) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Parse the data into a data tree
    lyd_parse_data_mem(ctx, data_copy, LYD_JSON, 0, LYD_VALIDATE_PRESENT, &node);

    // Free the data tree
    lyd_free_all(node);

    // Clean up
    free(data_copy);
    ly_ctx_destroy(ctx);

    return 0;
}