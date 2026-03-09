#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_string
  double ret_ucl_object_todouble_xdgwi = ucl_object_todouble(NULL);
  if (ret_ucl_object_todouble_xdgwi < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_string_ffpnd = ucl_parser_add_string(parser, (const char *)"r", (size_t )ret_ucl_object_todouble_xdgwi);
  if (ret_ucl_parser_add_string_ffpnd == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string to ucl_object_iterate_with_error
  ucl_object_t* ret_ucl_object_fromdouble_fvozp = ucl_object_fromdouble(-1);
  if (ret_ucl_object_fromdouble_fvozp == NULL){
  	return 0;
  }
  const ucl_object_t ajeqpyme;
  memset(&ajeqpyme, 0, sizeof(ajeqpyme));
  ucl_object_iter_t ret_ucl_object_iterate_new_njtft = ucl_object_iterate_new(&ajeqpyme);
  int ret_ucl_parser_get_default_priority_lzcau = ucl_parser_get_default_priority(parser);
  if (ret_ucl_parser_get_default_priority_lzcau < 0){
  	return 0;
  }

  const ucl_object_t* ret_ucl_object_iterate_with_error_kjwlb = ucl_object_iterate_with_error(ret_ucl_object_fromdouble_fvozp, &ret_ucl_object_iterate_new_njtft, ret_ucl_parser_add_string_ffpnd, &ret_ucl_parser_get_default_priority_lzcau);
  if (ret_ucl_object_iterate_with_error_kjwlb == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}