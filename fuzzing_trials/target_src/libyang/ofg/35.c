#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "/src/libyang/build/libyang/context.h" // Correct path for the header

ly_ext_data_clb dummy_callback(const struct ly_ctx *ctx, const char *module_name, void *user_data) {
    // Dummy callback function
    return NULL;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    struct ly_ctx *ctx = NULL;
    LY_ERR err;

    // Initialize the libyang context
    err = ly_ctx_new(NULL, 0, &ctx);
    if (err != LY_SUCCESS) {
        fprintf(stderr, "Failed to create context\n");
        return 0;
    }

    // Use the fuzzer data as user data for the callback
    void *user_data = (void *)data;

    // Call the function-under-test
    ly_ext_data_clb result = ly_ctx_set_ext_data_clb(ctx, dummy_callback, user_data);

    // Clean up
    ly_ctx_destroy(ctx);

    return 0;
}