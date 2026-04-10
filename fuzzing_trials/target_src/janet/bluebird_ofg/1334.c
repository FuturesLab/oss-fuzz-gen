#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1334(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table with janet_table_weakv

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table_weakv
    env = janet_table_weakv(JANET_SANDBOX_UNMARSHAL);
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_fiber_can_resume to janet_bytes_view
    Janet ret_janet_wrap_number_safe_foktm = janet_wrap_number_safe(JANET_NANBOX_64_POINTER_SHIFT);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_string_begin
    uint8_t* ret_janet_string_begin_ruqoy = janet_string_begin(1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_janet_string_begin_ruqoy == NULL){
    	return 0;
    }

    int ret_janet_bytes_view_shtqd = janet_bytes_view(ret_janet_wrap_number_safe_foktm, &ret_janet_string_begin_ruqoy, (int32_t *)&ret_janet_fiber_can_resume_qxofx);
    if (ret_janet_bytes_view_shtqd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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
    janet_dostring(env, str, source, &result);

    // Clean up
    free(str);
    janet_deinit();

    return 0;
}