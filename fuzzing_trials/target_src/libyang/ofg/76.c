#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *node = NULL;
    struct lyd_attr *attr = NULL;
    const char *module_data = "module test {namespace \"urn:test\"; prefix t; container cont {leaf leaf1 {type string;}}}";
    const char *attr_module = "urn:test";

    // Initialize libyang context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    // Parse the module data
    if (lys_parse_mem(ctx, module_data, LYS_IN_YANG, NULL) == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Create a dummy data tree node
    node = lyd_new_path(NULL, ctx, "/test:cont/leaf1", "dummy", 0, 0);
    if (node == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Ensure data is not NULL and has enough size to be used meaningfully
    if (size > 1) {
        // Use the first byte for attribute name length and the rest for the name
        size_t name_len = data[0] % size; // Ensure name length is within bounds
        char *attr_name = malloc(name_len + 1);
        if (attr_name == NULL) {
            lyd_free_all(node);
            ly_ctx_destroy(ctx);
            return 0;
        }
        memcpy(attr_name, data + 1, name_len);
        attr_name[name_len] = '\0';

        // Use the remaining data for attribute value
        const char *attr_value = (const char *)(data + 1 + name_len);

        // Call the function under test
        lyd_new_attr(node, attr_module, attr_name, attr_value, &attr);

        free(attr_name);
    }

    // Cleanup
    lyd_free_all(node);
    ly_ctx_destroy(ctx);

    return 0;
}