#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table with janet_table_weakk

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table_weakk with janet_table_weakv

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of janet_table_weakv

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table_weakv with janet_table_weakkv
    env = janet_table_weakkv(JANET_EV_TCTAG_ERR_STRINGF);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_core_env

    JanetTable* ret_janet_core_env_ytvcl = janet_core_env(env);
    if (ret_janet_core_env_ytvcl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_core_env to janet_table_to_struct


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_core_env to janet_table_merge_struct
    JanetKV* ret_janet_struct_begin_ozsld = janet_struct_begin(JANET_SANDBOX_ASM);
    if (ret_janet_struct_begin_ozsld == NULL){
    	return 0;
    }

    janet_table_merge_struct(env, ret_janet_struct_begin_ozsld);

    // End mutation: Producer.APPEND_MUTATOR

    JanetStruct ret_janet_table_to_struct_auivf = janet_table_to_struct(env);

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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_dostring to janet_abstract_decref

    int32_t ret_janet_abstract_decref_dywcz = janet_abstract_decref((void *)env);
    if (ret_janet_abstract_decref_dywcz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(str);
    janet_deinit();

    return 0;
}