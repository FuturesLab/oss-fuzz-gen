#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_858(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table with janet_table_weakv

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table_weakv
    env = janet_table_weakv(JANET_MAX_PROTO_DEPTH);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_core_env

    JanetTable* ret_janet_core_env_ytvcl = janet_core_env(env);
    if (ret_janet_core_env_ytvcl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_core_env to janet_table_init_raw
    JanetFiber ezyoqvqk;
    memset(&ezyoqvqk, 0, sizeof(ezyoqvqk));
    int ret_janet_fiber_can_resume_qxofx = janet_fiber_can_resume(&ezyoqvqk);
    if (ret_janet_fiber_can_resume_qxofx < 0){
    	return 0;
    }

    JanetTable* ret_janet_table_init_raw_olmgk = janet_table_init_raw(ret_janet_core_env_ytvcl, (int32_t )ret_janet_fiber_can_resume_qxofx);
    if (ret_janet_table_init_raw_olmgk == NULL){
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_dostring
    janet_dostring(ret_janet_table_init_raw_olmgk, str, source, &result);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(str);
    janet_deinit();

    return 0;
}