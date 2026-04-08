#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    struct lyd_node *parent = NULL;
    struct lyd_node *first_sibling = NULL;
    struct lyd_node *new_node = NULL;
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        return 0;
    }

    // Ensure that the input data is a valid NULL-terminated string
    char *path = (char *)malloc(size + 1);
    if (!path) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(path, data, size);
    path[size] = '\0';

    // Create a dummy value for the void pointer
    const char *value = "dummy_value";

    // Call the function-under-test
    lyd_new_path2(parent, ctx, path, value, 0, 0, 0, &first_sibling, &new_node);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_new_path2 to lyd_new_attr

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_new_path2 to lyd_any_copy_value
    lyd_free_all(new_node);
    int ret_ly_ctx_compiled_size_iwkhp = ly_ctx_compiled_size(ctx);
    if (ret_ly_ctx_compiled_size_iwkhp < 0){
    	return 0;
    }

    LY_ERR ret_lyd_any_copy_value_zpzof = lyd_any_copy_value(parent, new_node, (const char *)"w", (uint32_t )ret_ly_ctx_compiled_size_iwkhp);

    // End mutation: Producer.APPEND_MUTATOR

    ly_pattern_free((void *)new_node);
    const char nqxjhpvf[1024] = "qtqds";
    struct lyd_attr *dxtcxqad;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_pattern_free to lyd_any_value_str
    lyd_free_all(parent);

    LY_ERR ret_lyd_any_value_str_cvznh = lyd_any_value_str(parent, 0, new_node);

    // End mutation: Producer.APPEND_MUTATOR

    memset(&dxtcxqad, 0, sizeof(dxtcxqad));

    LY_ERR ret_lyd_new_attr_obscf = lyd_new_attr(first_sibling, nqxjhpvf, (const char *)"r", new_node, &dxtcxqad);

    // End mutation: Producer.APPEND_MUTATOR

    free(path);
    lyd_free_all(first_sibling);
    ly_ctx_destroy(ctx);

    return 0;
}