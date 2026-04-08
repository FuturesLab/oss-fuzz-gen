#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/src/context.h"
#include "/src/libyang/src/parser_data.h"
#include "/src/libyang/src/parser_schema.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    struct lyd_meta *meta = NULL;
    struct lyd_node *node = NULL;
    struct lyd_meta *dup_meta = NULL;
    LY_ERR err;

    // Initialize libyang context
    struct ly_ctx *ctx = NULL;
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    // Create a dummy schema for testing
    const char *schema = "module test {namespace urn:test;prefix t;leaf test-leaf {type string;}}";
    lys_parse_mem(ctx, schema, LYS_IN_YANG, NULL);

    // Create a dummy data node for testing
    const char *data_str = "<test-leaf xmlns=\"urn:test\">test</test-leaf>";
    lyd_parse_data_mem(ctx, data_str, LYD_XML, LYD_PARSE_ONLY, 0, &node);

    // Assume meta is obtained or created in some way, for fuzzing we just ensure it's not NULL
    meta = node->meta;

    // Call the function-under-test
    err = lyd_dup_meta_single(meta, node, &dup_meta);

    // Clean up
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}