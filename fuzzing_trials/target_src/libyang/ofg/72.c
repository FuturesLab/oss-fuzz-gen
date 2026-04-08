#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libyang/src/tree_data.h"
#include "/src/libyang/build/libyang/set.h"
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lyd_node *root = NULL;
    struct ly_set *set = NULL;
    const char *xpath = "/example-module:container/list[key='value']";
    LY_ERR err;

    // Initialize the libyang context
    if (ly_ctx_new(NULL, 0, &ctx) != LY_SUCCESS) {
        return 0;
    }

    // Parse some example data into a data tree
    const char *example_data = "<container xmlns=\"urn:example-module\">"
                               "<list><key>value</key></list>"
                               "</container>";
    if (lyd_parse_data_mem(ctx, example_data, LYD_XML, 0, &root) != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the fuzz data and copy it
    char *fuzz_data = (char *)malloc(size + 1);
    if (!fuzz_data) {
        lyd_free_all(root);
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(fuzz_data, data, size);
    fuzz_data[size] = '\0';

    // Call the function-under-test
    err = lyd_find_xpath(root, xpath, &set);

    // Clean up
    lyd_free_all(root);
    ly_set_free(set, NULL);
    free(fuzz_data);
    ly_ctx_destroy(ctx);

    return 0;
}