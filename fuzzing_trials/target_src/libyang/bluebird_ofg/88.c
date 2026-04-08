#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    LY_ERR err;
    char *search_dir = NULL;
    void *user_data = (void *)0x1; // Dummy non-NULL pointer

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create libyang context\n");
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *data_str = (char *)malloc(size + 1);
    if (!data_str) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Call the function-under-test
    err = ly_ctx_get_yanglib_data(ctx, &node, data_str, user_data);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_get_yanglib_data to lyd_validate_op
    struct lyd_node* ret_lyd_child_no_keys_gqypo = lyd_child_no_keys(node);
    if (ret_lyd_child_no_keys_gqypo == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_child_no_keys to lyd_find_sibling_first
    lyd_free_siblings(ret_lyd_child_no_keys_gqypo);
    struct lyd_node* ret_lyd_first_sibling_gmirv = lyd_first_sibling(NULL);
    if (ret_lyd_first_sibling_gmirv == NULL){
    	return 0;
    }

    LY_ERR ret_lyd_find_sibling_first_rvtxq = lyd_find_sibling_first(ret_lyd_child_no_keys_gqypo, ret_lyd_first_sibling_gmirv, &ret_lyd_child_no_keys_gqypo);

    // End mutation: Producer.APPEND_MUTATOR

    LY_ERR ret_lyd_validate_op_lstxx = lyd_validate_op(node, ret_lyd_child_no_keys_gqypo, 0, &node);

    // End mutation: Producer.APPEND_MUTATOR

    lyd_free_all(node);
    ly_ctx_destroy(ctx);
    free(data_str);

    return 0;
}