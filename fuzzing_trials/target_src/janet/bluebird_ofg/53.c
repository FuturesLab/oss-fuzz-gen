#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to work with
    }

    // Initialize Janet
    janet_init();

    // Prepare the JanetTable parameter
    JanetTable *env = janet_table(0);

    // Prepare the string parameters

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_env_lookup_into
    JanetTable jasrmipy;
    memset(&jasrmipy, 0, sizeof(jasrmipy));
    JanetTable* ret_janet_table_clone_mvsop = janet_table_clone(&jasrmipy);
    if (ret_janet_table_clone_mvsop == NULL){
    	return 0;
    }
    void* ret_janet_malloc_wgnun = janet_malloc(JANET_FILE_UPDATE);
    if (ret_janet_malloc_wgnun == NULL){
    	return 0;
    }

    janet_env_lookup_into(&jasrmipy, env, (const char *)ret_janet_malloc_wgnun, JANET_EV_TCTAG_ERR_STRING);

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