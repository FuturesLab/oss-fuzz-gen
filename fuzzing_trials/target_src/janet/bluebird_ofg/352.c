#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to work with
    }

    // Initialize Janet
    janet_init();

    // Prepare the JanetTable parameter
    JanetTable *env = janet_table(0);

    // Prepare the string parameters

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_env_lookup_into
    void* ret_janet_malloc_sbksl = janet_malloc(JANET_SANDBOX_DYNAMIC_MODULES);
    if (ret_janet_malloc_sbksl == NULL){
    	return 0;
    }

    janet_env_lookup_into(env, env, (const char *)ret_janet_malloc_sbksl, JANET_SANDBOX_FFI_USE);

    // End mutation: Producer.APPEND_MUTATOR

    char *source = (char *)malloc(size + 1);
    if (!source) {
        janet_deinit();
        return 0;
    }
    memcpy(source, data, size);
    source[size] = '\0'; // Ensure null-terminated

    const char *source_name = "fuzz_source"; // A simple source name

    // Prepare the Janet result parameter
    Janet result;

    // Call the function-under-test
    janet_dostring(env, source, source_name, &result);

    // Clean up
    free(source);
    janet_deinit();

    return 0;
}