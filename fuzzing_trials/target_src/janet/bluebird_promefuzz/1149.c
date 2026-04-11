#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1149(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare dummy file
    write_dummy_file(Data, Size);

    // Initialize Janet environment
    janet_init();

    // Prepare Janet source and environment
    Janet source = janet_stringv(Data, Size);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table
    JanetTable *env = janet_table(JANET_STACKFRAME_ENTRANCE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    const uint8_t *where = (const uint8_t *)"./dummy_file";

    // Fuzz janet_compile
    JanetCompileResult compileResult = janet_compile(source, env, where);
    if (compileResult.status == JANET_COMPILE_OK) {
        // Fuzz janet_description
        JanetString description = janet_description(source);

        // Fuzz janet_string_equal
        int stringEqual = janet_string_equal(where, description);

        // Fuzz janet_to_string
        JanetString toString = janet_to_string(source);

        // Prepare an array of Janet for janet_getstring
        Janet array[1] = {source};

        // Ensure the index is within bounds and the Janet type is a string
        if (Size > 1 && janet_checktype(source, JANET_STRING)) {
            int32_t index = 0;  // Only index 0 is valid in this array
            // Fuzz janet_getstring
            JanetString getString = janet_getstring(array, index);
        }

        // Fuzz janet_unwrap_string
        if (janet_checktype(source, JANET_STRING)) {
            JanetString unwrapString = janet_unwrap_string(source);
        }
    }

    // Cleanup Janet environment
    janet_deinit();

    return 0;
}