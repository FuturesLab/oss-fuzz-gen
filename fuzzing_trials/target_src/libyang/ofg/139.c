#include <stdint.h>
#include <stdlib.h>
#include "/src/libyang/build/libyang/context.h"

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Create a new libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS || ctx == NULL) {
        return 0;
    }

    // Call the function-under-test
    uint16_t change_count = ly_ctx_get_change_count(ctx);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}