#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data to create a data tree
    lyd_parse_data_mem(ctx, input_data, LYD_JSON, LYD_PARSE_ONLY, 0, &root);

    // Call the function-under-test if the root is a list node
    if (root && root->schema->nodetype == LYS_LIST) {
        uint32_t pos = lyd_list_pos(root);
    }

    // Clean up
    lyd_free_all(root);
    ly_ctx_destroy(ctx);
    free(input_data);

    return 0;
}

#ifdef __cplusplus
}
#endif