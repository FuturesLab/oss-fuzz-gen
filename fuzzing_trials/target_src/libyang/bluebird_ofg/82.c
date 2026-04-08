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

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
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
    lys_parse_mem(ctx, yang_module, LYS_IN_YANG, NULL);

    // Create a simple XML data tree for testing
    const char *xml_data = "<top xmlns=\"urn:test\"><name>test</name></top>";
    lyd_parse_data_mem(ctx, xml_data, LYD_XML, 0, LYD_VALIDATE_PRESENT, &root);

    // Ensure the data is non-null and null-terminate it
    char *xpath_expr = NULL;
    if (size > 0) {
        xpath_expr = (char *)malloc(size + 1);
        if (!xpath_expr) {
            ly_ctx_destroy(ctx);
            
            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lyd_new_path2
            struct lyd_node rrixhlzo;
            memset(&rrixhlzo, 0, sizeof(rrixhlzo));
            lyd_free_siblings(&rrixhlzo);
            ly_pattern_free((void *)ctx);
            struct lyd_node* ret_lyd_first_sibling_kkyfl = lyd_first_sibling(root);
            if (ret_lyd_first_sibling_kkyfl == NULL){
            	return 0;
            }

            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_internal_modules_count with ly_ctx_get_options
            uint32_t ret_ly_ctx_internal_modules_count_nsvnt = ly_ctx_get_options(ctx);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR


            if (ret_ly_ctx_internal_modules_count_nsvnt < 0){
            	return 0;
            }
            struct lyd_node* ret_lyd_first_sibling_hbjsp = lyd_first_sibling(root);
            if (ret_lyd_first_sibling_hbjsp == NULL){
            	return 0;
            }


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_first_sibling to lyd_insert_sibling
            struct lyd_node hkspfhwv;
            memset(&hkspfhwv, 0, sizeof(hkspfhwv));
            LY_ERR ret_lyd_unlink_tree_uckhc = lyd_unlink_tree(&hkspfhwv);
            struct lyd_node* ret_lyd_child_no_keys_sxwdn = lyd_child_no_keys(NULL);
            if (ret_lyd_child_no_keys_sxwdn == NULL){
            	return 0;
            }

            LY_ERR ret_lyd_insert_sibling_ujxoa = lyd_insert_sibling(&hkspfhwv, ret_lyd_child_no_keys_sxwdn, &ret_lyd_first_sibling_kkyfl);

            // End mutation: Producer.APPEND_MUTATOR


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_insert_sibling to lyd_find_path
            lyd_free_tree(ret_lyd_first_sibling_kkyfl);
            ly_pattern_free((void *)&rrixhlzo);
            ly_bool ret_lyd_is_default_zmxom = lyd_is_default(root);

            LY_ERR ret_lyd_find_path_oghwp = lyd_find_path(ret_lyd_first_sibling_kkyfl, &rrixhlzo, ret_lyd_is_default_zmxom, &ret_lyd_child_no_keys_sxwdn);

            // End mutation: Producer.APPEND_MUTATOR

            LY_ERR ret_lyd_new_path2_xpvuz = lyd_new_path2(&rrixhlzo, ctx, ctx, (const void *)ret_lyd_first_sibling_kkyfl, 64, 0, ret_ly_ctx_internal_modules_count_nsvnt, &ret_lyd_first_sibling_hbjsp, &root);

            // End mutation: Producer.APPEND_MUTATOR


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lyd_new_path2 to lyd_any_copy_value
            lyd_free_tree(root);
            ly_pattern_free((void *)&rrixhlzo);

            LY_ERR ret_lyd_any_copy_value_nptrk = lyd_any_copy_value(root, ret_lyd_first_sibling_hbjsp, &rrixhlzo, LYD_HT_MIN_ITEMS);

            // End mutation: Producer.APPEND_MUTATOR

return 0;
        }
        memcpy(xpath_expr, data, size);
        xpath_expr[size] = '\0';
    }

    // Call the function-under-test
    lyd_find_xpath(root, xpath_expr, &set);

    // Cleanup

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_free_all with lyd_free_siblings
    lyd_free_siblings(root);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    ly_set_free(set, NULL);  // Pass NULL for the destructor

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ly_ctx_destroy with ly_ctx_free_parsed
    ly_ctx_free_parsed(ctx);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    free(xpath_expr);

    return 0;
}