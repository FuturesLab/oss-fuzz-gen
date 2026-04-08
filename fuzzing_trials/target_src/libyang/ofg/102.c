#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/build/libyang/set.h"
#include "/src/libyang/build/libyang/log.h"
#include "/src/libyang/build/libyang/tree.h"
#include "/src/libyang/build/libyang/context.h"
#include "/src/libyang/src/in.h"
#include "/src/libyang/src/tree_schema.h"  // Include for LYD_VALIDATE_PRESENT
#include "/src/libyang/src/parser_data.h"  // Include for lyd_parse_data_mem

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
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
    lyd_free_all(root);
    ly_set_free(set, NULL);  // Pass NULL for the destructor
    ly_ctx_destroy(ctx);
    free(xpath_expr);

    return 0;
}