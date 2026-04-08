#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/set.h"
#include "/src/libyang/src/log.h"
#include "/src/libyang/src/tree.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/in.h"
#include "/src/libyang/src/tree_schema.h"  // Include for LYD_VALIDATE_PRESENT
#include "/src/libyang/src/parser_data.h"  // Include for lyd_parse_data_mem

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct ly_set *set = NULL;
    LY_ERR err;

    // Initialize libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Create a simple YANG module for testing
    const char *yang_module = "module test {namespace urn:test;prefix t; container top {leaf name {type string;}}}";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_new to lyd_parse_data_mem
    uint32_t ret_ly_ctx_get_modules_hash_zkrtr = ly_ctx_get_modules_hash(ctx);
    if (ret_ly_ctx_get_modules_hash_zkrtr < 0){
    	return 0;
    }
    const char rfrywikk[1024] = "oycun";
    struct lyd_node *xtmvutar;
    memset(&xtmvutar, 0, sizeof(xtmvutar));

    LY_ERR ret_lyd_parse_data_mem_vbqor = lyd_parse_data_mem(ctx, rfrywikk, 0, ret_ly_ctx_get_modules_hash_zkrtr, 1, &xtmvutar);

    // End mutation: Producer.APPEND_MUTATOR

    lys_parse_mem(ctx, yang_module, LYS_IN_YANG, NULL);

    // Create a simple XML data tree for testing
    const char *xml_data = "<top xmlns=\"urn:test\"><name>test</name></top>";

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of lyd_parse_data_mem
    lyd_parse_data_mem(ctx, xml_data, LYD_XML, 0, LYD_VALIDATE_PRESENT, &root);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Ensure the data is non-null and null-terminate it
    char *xpath_expr = NULL;
    if (size > 0) {
        xpath_expr = (char *)malloc(size + 1);
        if (!xpath_expr) {
            ly_ctx_destroy(ctx);
            
            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lyd_parse_value_fragment
            ly_pattern_free((void *)ctx);
            uint32_t ret_ly_ctx_get_options_lpcly = ly_ctx_get_options(ctx);
            if (ret_ly_ctx_get_options_lpcly < 0){
            	return 0;
            }
            int ret_ly_ctx_compiled_size_lwxwy = ly_ctx_compiled_size(ctx);
            if (ret_ly_ctx_compiled_size_lwxwy < 0){
            	return 0;
            }
            struct lyd_node* ret_lyd_child_no_keys_eadwj = lyd_child_no_keys(xtmvutar);
            if (ret_lyd_child_no_keys_eadwj == NULL){
            	return 0;
            }

            LY_ERR ret_lyd_parse_value_fragment_itlpr = lyd_parse_value_fragment(ctx, ctx, NULL, 0, 0, ret_ly_ctx_get_options_lpcly, (uint32_t )ret_ly_ctx_compiled_size_lwxwy, &ret_lyd_child_no_keys_eadwj);

            // End mutation: Producer.APPEND_MUTATOR

return 0;
        }
        memcpy(xpath_expr, data, size);
        xpath_expr[size] = '\0';
    }

    // Call the function-under-test
    lyd_find_xpath(root, xpath_expr, &set);

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_find_xpath to lyd_merge_module
    struct lyd_node* ret_lyd_child_no_keys_bluia = lyd_child_no_keys(root);
    if (ret_lyd_child_no_keys_bluia == NULL){
    	return 0;
    }
    lyd_free_all(xtmvutar);
    uint16_t ret_ly_ctx_get_change_count_krggz = ly_ctx_get_change_count(ctx);
    if (ret_ly_ctx_get_change_count_krggz < 0){
    	return 0;
    }

    LY_ERR ret_lyd_merge_module_vuryh = lyd_merge_module(&ret_lyd_child_no_keys_bluia, xtmvutar, NULL, NULL, (void *)set, ret_ly_ctx_get_change_count_krggz);

    // End mutation: Producer.APPEND_MUTATOR

    lyd_free_all(root);
    ly_set_free(set, NULL);  // Pass NULL for the destructor
    ly_ctx_destroy(ctx);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lys_parse_fd
    int ret_ly_ctx_compiled_size_tpiuq = ly_ctx_compiled_size(NULL);
    if (ret_ly_ctx_compiled_size_tpiuq < 0){
    	return 0;
    }

    LY_ERR ret_lys_parse_fd_ynnjk = lys_parse_fd(ctx, ret_ly_ctx_compiled_size_tpiuq, 0, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    free(xpath_expr);

    return 0;
}