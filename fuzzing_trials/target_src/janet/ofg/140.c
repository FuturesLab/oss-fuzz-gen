#include <stdint.h>
#include <stddef.h>
#include "/src/janet/src/include/janet.h" // Corrected path for JanetVM

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Initialize JanetVM
    janet_init();

    // Check if data is not null and size is greater than zero
    if (data != NULL && size > 0) {
        // Convert the input data into a Janet string or buffer
        JanetBuffer *buffer = janet_buffer(size);
        janet_buffer_push_bytes(buffer, data, size);

        // Create a Janet array to hold the buffer
        Janet argv[1];
        argv[0] = janet_wrap_buffer(buffer);

        // Resolve the environment and symbol
        JanetTable *env = janet_core_env(NULL);
        JanetSymbol sym = janet_csymbol("function_under_test");
        Janet fun;
        if (janet_resolve(env, sym, &fun) && janet_checktype(fun, JANET_FUNCTION)) {
            janet_call(janet_unwrap_function(fun), 1, argv);
        }

        // Clean up the buffer
        janet_buffer_deinit(buffer);
    }

    // Clean up the JanetVM if necessary
    janet_deinit();

    return 0;
}

#ifdef __cplusplus
}
#endif