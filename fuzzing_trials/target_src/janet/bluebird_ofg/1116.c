#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1116(const uint8_t *data, size_t size) {
    JanetTable *env;
    char *str;
    char *source;
    Janet result;

    // Initialize the Janet environment
    janet_init();

    // Create a new environment table

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table with janet_table_weakk

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function janet_table_weakk with janet_table_weakv
    env = janet_table_weakv(0);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Allocate memory for the string and copy the data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table to janet_core_env

    JanetTable* ret_janet_core_env_ytvcl = janet_core_env(env);
    if (ret_janet_core_env_ytvcl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_core_env to janet_table_find
    JanetParser hmlhxawb;
    memset(&hmlhxawb, 0, sizeof(hmlhxawb));
    Janet ret_janet_parser_produce_wrapped_unnjy = janet_parser_produce_wrapped(&hmlhxawb);

    JanetKV* ret_janet_table_find_hfszt = janet_table_find(env, ret_janet_parser_produce_wrapped_unnjy);
    if (ret_janet_table_find_hfszt == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from janet_table_find to janet_compile_lint
    Janet ret_janet_wrap_u64_dgqxf = janet_wrap_u64(JANET_SANDBOX_FS_WRITE);
    JanetArray* ret_janet_array_dzleg = janet_array(JANET_FILE_READ);
    if (ret_janet_array_dzleg == NULL){
    	return 0;
    }
    const uint8_t kdajpfrv = 64;

    JanetCompileResult ret_janet_compile_lint_txlcn = janet_compile_lint(ret_janet_wrap_u64_dgqxf, env, &kdajpfrv, ret_janet_array_dzleg);

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