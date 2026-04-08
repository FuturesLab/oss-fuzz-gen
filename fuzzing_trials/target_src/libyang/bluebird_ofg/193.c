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

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
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
            return 0;
        }
        memcpy(xpath_expr, data, size);
        xpath_expr[size] = '\0';
    }

    // Call the function-under-test
    lyd_find_xpath(root, xpath_expr, &set);

    // Cleanup

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function lyd_free_all with lyd_free_tree
    lyd_free_tree(root);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    ly_set_free(set, NULL);  // Pass NULL for the destructor
    ly_ctx_destroy(ctx);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ly_ctx_destroy to lyd_parse_data_path
    int ret_ly_time_tz_offset_at_ktcqk = ly_time_tz_offset_at(0);
    if (ret_ly_time_tz_offset_at_ktcqk < 0){
    	return 0;
    }
    struct lyd_node *druspwql;
    memset(&druspwql, 0, sizeof(druspwql));

    LY_ERR ret_lyd_parse_data_path_luaqg = lyd_parse_data_path(ctx, (const char *)"w", 0, 1, (uint32_t )ret_ly_time_tz_offset_at_ktcqk, &druspwql);

    // End mutation: Producer.APPEND_MUTATOR

    free(xpath_expr);

    return 0;
}