#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to work with
    }

    // Initialize Janet
    janet_init();

    // Prepare the JanetTable parameter
    JanetTable *env = janet_table(0);

    // Prepare the string parameters

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_env_lookup_into
    JanetTable* ret_janet_table_weakk_cttjn = janet_table_weakk(-1);
    if (ret_janet_table_weakk_cttjn == NULL){
    	return 0;
    }
    void* ret_janet_malloc_jqbaj = janet_malloc(JANET_EV_TCTAG_INTEGER);
    if (ret_janet_malloc_jqbaj == NULL){
    	return 0;
    }

    janet_env_lookup_into(env, ret_janet_table_weakk_cttjn, (const char *)ret_janet_malloc_jqbaj, JANET_PRETTY_ONELINE);

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