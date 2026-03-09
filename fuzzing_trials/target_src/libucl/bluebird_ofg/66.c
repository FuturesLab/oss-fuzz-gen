#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_merge
  ucl_object_t* ret_ucl_object_fromdouble_yceet = ucl_object_fromdouble(UCL_PRIORITY_MAX);
  if (ret_ucl_object_fromdouble_yceet == NULL){
  	return 0;
  }
  ucl_object_t* ret_ucl_object_fromdouble_fqaam = ucl_object_fromdouble(UCL_PRIORITY_MIN);
  if (ret_ucl_object_fromdouble_fqaam == NULL){
  	return 0;
  }


  // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_merge with ucl_array_merge
  bool ret_ucl_object_merge_gpnqn = ucl_array_merge(ret_ucl_object_fromdouble_yceet, ret_ucl_object_fromdouble_fqaam, result);
  // End mutation: Producer.REPLACE_FUNC_MUTATOR


  if (ret_ucl_object_merge_gpnqn == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}