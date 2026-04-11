#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static Janet dummy_cfunction(int32_t argc, Janet *argv) {
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_384(const uint8_t *Data, size_t Size) {
    // Initialize Janet VM
    janet_init();

    // Prepare the environment
    JanetTable env;
    memset(&env, 0, sizeof(JanetTable));
    janet_table_init(&env, 0);

    // Ensure the input is null-terminated for janet_dostring
    char *inputString = (char *)malloc(Size + 1);
    if (!inputString) {
        janet_deinit();
        return 0; // Exit if malloc fails
    }
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Fuzz janet_dostring
    Janet result;
    janet_dostring(&env, inputString, "./dummy_file", &result);

    // Fuzz janet_register
    janet_register("dummy_function", dummy_cfunction);

    // Fuzz janet_getcfunction
    Janet argv[] = { janet_wrap_cfunction(dummy_cfunction) };
    JanetCFunction cfun = janet_getcfunction(argv, 0);

    // Fuzz janet_optcfunction
    JanetCFunction optCfun = janet_optcfunction(argv, 1, 0, dummy_cfunction);

    // Fuzz janet_wrap_cfunction
    Janet wrapped = janet_wrap_cfunction(dummy_cfunction);

    // Clean up
    free(inputString);
    janet_table_deinit(&env);

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}