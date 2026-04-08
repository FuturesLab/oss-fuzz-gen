#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *parent = NULL;
    struct lyd_node *new_node = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Ensure the input data is large enough to be split into meaningful parts
    if (size < 8) { // Increase the minimum size to ensure meaningful input
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Split the input data into four parts for name, value, module_name, and prefix
    size_t part_size = size / 4;
    char *name = (char *)malloc(part_size + 1);
    char *value = (char *)malloc(part_size + 1);
    char *module_name = (char *)malloc(part_size + 1);
    char *prefix = (char *)malloc(part_size + 1);

    if (!name || !value || !module_name || !prefix) {
        fprintf(stderr, "Memory allocation failed\n");
        ly_ctx_destroy(ctx);
        free(name);
        free(value);
        free(module_name);
        free(prefix);
        return 0;
    }

    memcpy(name, data, part_size);
    memcpy(value, data + part_size, part_size);
    memcpy(module_name, data + 2 * part_size, part_size);
    memcpy(prefix, data + 3 * part_size, part_size);

    name[part_size] = '\0';
    value[part_size] = '\0';
    module_name[part_size] = '\0';
    prefix[part_size] = '\0';

    // Validate the strings to prevent invalid input
    if (strlen(name) == 0 || strlen(module_name) == 0) {
        fprintf(stderr, "Invalid input data\n");
        ly_ctx_destroy(ctx);
        free(name);
        free(value);
        free(module_name);
        free(prefix);
        return 0;
    }

    // Call the function-under-test with non-null input
    err = lyd_new_opaq(parent, ctx, name, value, module_name, prefix, &new_node);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "lyd_new_opaq failed\n");
    }

    // Clean up
    lyd_free_all(new_node);
    ly_ctx_destroy(ctx);
    free(name);
    free(value);
    free(module_name);
    free(prefix);

    return 0;
}