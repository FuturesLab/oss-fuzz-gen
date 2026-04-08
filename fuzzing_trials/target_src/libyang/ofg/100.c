#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    struct lys_module *module = NULL;
    char *namespace = NULL;
    LY_ERR err;

    // Initialize the context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS || ctx == NULL) {
        return 0;
    }

    // Load a YANG module into the context for testing purposes
    const char *yang_data = "module test { namespace \"urn:test\"; prefix t; }";
    err = lys_parse_mem(ctx, yang_data, LYS_IN_YANG, &module);
    if (err != LY_SUCCESS) {
        ly_ctx_destroy(ctx);
        return 0;
    }

    // Allocate memory for the namespace string and ensure it's null-terminated
    namespace = (char *)malloc(size + 1);
    if (namespace == NULL) {
        ly_ctx_destroy(ctx);
        return 0;
    }
    memcpy(namespace, data, size);
    namespace[size] = '\0';

    // Call the function-under-test
    module = ly_ctx_get_module_latest_ns(ctx, namespace);

    // Clean up
    free(namespace);
    ly_ctx_destroy(ctx);

    return 0;
}