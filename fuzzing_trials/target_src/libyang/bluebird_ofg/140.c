#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/tree_schema.h"
#include "/src/libyang/src/validation.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_node *tree = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a dummy schema for testing
    const char *schema = "module test {namespace urn:test;prefix t;yang-version 1.1; container test-container {leaf test-leaf {type string;}}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Create a dummy data tree
    const char *data_tree = "<test-container xmlns=\"urn:test\"><test-leaf>test</test-leaf></test-container>";
    lyd_parse_data_mem(ctx, data_tree, LYD_XML, LYD_PARSE_ONLY, LYD_VALIDATE_PRESENT, &node);

    // Allocate and copy input data to a buffer
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into a data tree
    lyd_parse_data_mem(ctx, input_data, LYD_XML, LYD_PARSE_ONLY, LYD_VALIDATE_PRESENT, &tree);

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_parse_data_mem to lyd_parse_data
    LY_ERR ret_ly_ctx_compile_dqmae = ly_ctx_compile(ctx);
    uint32_t ret_ly_ctx_internal_modules_count_aafkv = ly_ctx_internal_modules_count(ctx);
    if (ret_ly_ctx_internal_modules_count_aafkv < 0){
    	return 0;
    }
    struct lyd_node *cjjgvful;
    memset(&cjjgvful, 0, sizeof(cjjgvful));

    LY_ERR ret_lyd_parse_data_hsuco = lyd_parse_data(ctx, node, NULL, 0, 64, ret_ly_ctx_internal_modules_count_aafkv, &cjjgvful);

    // End mutation: Producer.APPEND_MUTATOR

    lyd_validate_op(node, tree, LYD_TYPE_DATA_YANG, &tree);

    // Clean up
    lyd_free_all(node);
    lyd_free_all(tree);
    ly_ctx_destroy(ctx);
    free(input_data);

    return 0;
}