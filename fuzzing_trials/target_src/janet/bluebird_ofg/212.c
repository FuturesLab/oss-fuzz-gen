#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table
    env = janet_table(JANET_RECURSION_GUARD);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_wrap_pointer

    Janet ret_janet_wrap_pointer_wbtud = janet_wrap_pointer((void *)env);

    // End mutation: Producer.APPEND_MUTATOR

    str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0'; // Null-terminate the string

    // Set a dummy source name
    source = (char *)"fuzz_input";

    // Call the function-under-test
    janet_dostring(env, str, source, &result);

    // Clean up
    free(str);
    janet_deinit();

    return 0;
}