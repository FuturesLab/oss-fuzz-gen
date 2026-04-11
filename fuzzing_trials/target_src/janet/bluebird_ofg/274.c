#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table
    env = janet_table(0);

    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_core_env


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_core_env with janet_table_clone
    JanetTable* ret_janet_core_env_ytvcl = janet_table_clone(env);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_janet_core_env_ytvcl == NULL){
    	return 0;
    }

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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_dostring to janet_checkabstract

    JanetAbstract ret_janet_checkabstract_oxtnf = janet_checkabstract(result, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    free(str);
    janet_deinit();

    return 0;
}