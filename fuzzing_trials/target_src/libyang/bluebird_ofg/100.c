#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/validation.h"
#include "/src/libyang/src/tree.h"
#include "/src/libyang/src/context.h"

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *tree = NULL;
    const struct lysc_ext_instance *ext_instance = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Parse the input data into a data tree
    char *data_str = malloc(size + 1);
    if (data_str == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    lyd_parse_data_mem(ctx, data_str, LYD_XML, LYD_PARSE_ONLY, 0, &node);

    // Call the function-under-test
    err = lyd_validate_ext(&node, ext_instance, 0, &tree);

    // Clean up
    lyd_free_all(node);
    lyd_free_all(tree);
    ly_ctx_destroy(ctx);
    free(data_str);

    return 0;
}