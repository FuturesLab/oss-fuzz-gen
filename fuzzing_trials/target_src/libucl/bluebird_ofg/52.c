#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_new to ucl_parser_add_fd
  const ucl_object_t egyxkhzh;
  memset(&egyxkhzh, 0, sizeof(egyxkhzh));
  double ret_ucl_object_todouble_kqead = ucl_object_todouble(&egyxkhzh);
  if (ret_ucl_object_todouble_kqead < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_fd_qnoam = ucl_parser_add_fd(parser, (int )ret_ucl_object_todouble_kqead);
  if (ret_ucl_parser_add_fd_qnoam == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_merge
  ucl_object_t* ret_ucl_object_fromdouble_egqiz = ucl_object_fromdouble(-1);
  if (ret_ucl_object_fromdouble_egqiz == NULL){
  	return 0;
  }
  ucl_object_t eqbedmyq;

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromdouble to ucl_object_tolstring_safe
  char* ret_ucl_copy_value_trash_usfeb = ucl_copy_value_trash(ret_ucl_object_fromdouble_egqiz);
  if (ret_ucl_copy_value_trash_usfeb == NULL){
  	return 0;
  }
  const ucl_object_t bjrqodsq;

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_copy_value_trash to ucl_object_insert_key
  ucl_object_t* ret_ucl_object_fromdouble_balre = ucl_object_fromdouble(0);
  if (ret_ucl_object_fromdouble_balre == NULL){
  	return 0;
  }
  int64_t ret_ucl_object_toint_omjxp = ucl_object_toint(ret_ucl_object_fromdouble_egqiz);
  if (ret_ucl_object_toint_omjxp < 0){
  	return 0;
  }

  bool ret_ucl_object_insert_key_xpeqb = ucl_object_insert_key(NULL, ret_ucl_object_fromdouble_balre, ret_ucl_copy_value_trash_usfeb, (size_t )ret_ucl_object_toint_omjxp, 1);
  if (ret_ucl_object_insert_key_xpeqb == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  memset(&bjrqodsq, 0, sizeof(bjrqodsq));
  double ret_ucl_object_todouble_npebt = ucl_object_todouble(&bjrqodsq);
  if (ret_ucl_object_todouble_npebt < 0){
  	return 0;
  }

  bool ret_ucl_object_tolstring_safe_tvmzt = ucl_object_tolstring_safe(ret_ucl_object_fromdouble_egqiz, &ret_ucl_copy_value_trash_usfeb, (size_t *)&ret_ucl_object_todouble_npebt);
  if (ret_ucl_object_tolstring_safe_tvmzt == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  memset(&eqbedmyq, 0, sizeof(eqbedmyq));
  ucl_object_t* ret_ucl_array_pop_last_gvhtj = ucl_array_pop_last(&eqbedmyq);
  if (ret_ucl_array_pop_last_gvhtj == NULL){
  	return 0;
  }

  bool ret_ucl_object_merge_fyrzq = ucl_object_merge(ret_ucl_object_fromdouble_egqiz, &eqbedmyq, result);
  if (ret_ucl_object_merge_fyrzq == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}