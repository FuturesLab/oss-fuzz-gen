#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_string
  const ucl_object_t tqcjshsg;
  memset(&tqcjshsg, 0, sizeof(tqcjshsg));
  char* ret_ucl_copy_value_trash_imfem = ucl_copy_value_trash(&tqcjshsg);
  if (ret_ucl_copy_value_trash_imfem == NULL){
  	return 0;
  }

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_copy_value_trash to ucl_comments_add

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_copy_value_trash to ucl_object_lookup_path_char
  ucl_object_t* ret_ucl_object_fromdouble_depdu = ucl_object_fromdouble(0);
  if (ret_ucl_object_fromdouble_depdu == NULL){
  	return 0;
  }
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_ymgvd = ucl_object_emit_memory_funcs((void **)&parser);
  if (ret_ucl_object_emit_memory_funcs_ymgvd == NULL){
  	return 0;
  }

  const ucl_object_t* ret_ucl_object_lookup_path_char_lqani = ucl_object_lookup_path_char(ret_ucl_object_fromdouble_depdu, &parser, *ret_ucl_copy_value_trash_imfem);
  if (ret_ucl_object_lookup_path_char_lqani == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_object_t* ret_ucl_object_fromstring_iltke = ucl_object_fromstring(ret_ucl_copy_value_trash_imfem);
  if (ret_ucl_object_fromstring_iltke == NULL){
  	return 0;
  }

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_fromstring to ucl_array_tail

  const ucl_object_t* ret_ucl_array_tail_povof = ucl_array_tail(ret_ucl_object_fromstring_iltke);
  if (ret_ucl_array_tail_povof == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_object_t* ret_ucl_object_typed_new_gnlcv = ucl_object_typed_new(0);
  if (ret_ucl_object_typed_new_gnlcv == NULL){
  	return 0;
  }

  ucl_comments_add(ret_ucl_object_fromstring_iltke, ret_ucl_object_typed_new_gnlcv, ret_ucl_copy_value_trash_imfem);

  // End mutation: Producer.APPEND_MUTATOR

  int ret_ucl_parser_get_default_priority_gkkng = ucl_parser_get_default_priority(parser);
  if (ret_ucl_parser_get_default_priority_gkkng < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_string_cfrcj = ucl_parser_add_string(parser, ret_ucl_copy_value_trash_imfem, (size_t )ret_ucl_parser_get_default_priority_gkkng);
  if (ret_ucl_parser_add_string_cfrcj == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}