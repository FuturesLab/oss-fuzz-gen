#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static JanetTable *create_dummy_env() {
    JanetTable *env = janet_table(0);
    return env;
}

int LLVMFuzzerTestOneInput_1184(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize the Janet VM
    janet_init();

    // Prepare environment for janet_compile
    JanetTable *env = create_dummy_env();

    // Prepare dummy file
    prepare_dummy_file(Data, Size);

    // Fuzz janet_compile
    Janet source = janet_stringv(Data, Size);
    JanetString where = (JanetString)"./dummy_file";
    JanetCompileResult compile_result = janet_compile(source, env, where);

    // Check compile result
    if (compile_result.status == JANET_COMPILE_OK) {
        // Fuzz janet_description
        JanetString description = janet_description(source);

        // Fuzz janet_to_string
        JanetString to_string = janet_to_string(source);

        // Fuzz janet_string_equal
        int equal_result = janet_string_equal(description, to_string);

        // Prepare array for janet_getstring
        Janet array[2] = { source, janet_wrap_string(description) };

        // Fuzz janet_getstring
        JanetString getstring_result = janet_getstring(array, 1);

        // Fuzz janet_unwrap_string
        JanetString unwrap_result = janet_unwrap_string(source);
    }

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}