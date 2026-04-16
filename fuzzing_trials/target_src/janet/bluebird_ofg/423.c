#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_423(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table
    env = janet_table(JANET_SANDBOX_HRTIME);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_env_lookup_into
    JanetTable* ret_janet_table_weakk_tzgue = janet_table_weakk(JANET_STACKFRAME_TAILCALL);
    if (ret_janet_table_weakk_tzgue == NULL){
    	return 0;
    }

    janet_env_lookup_into(env, ret_janet_table_weakk_tzgue, (const char *)"r", JANET_EV_TCTAG_ERR_STRINGF);

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