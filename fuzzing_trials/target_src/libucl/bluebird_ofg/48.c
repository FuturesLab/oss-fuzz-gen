#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
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
  int ret_ucl_parser_get_default_priority_gkkng = ucl_parser_get_default_priority(parser);
  if (ret_ucl_parser_get_default_priority_gkkng < 0){
  	return 0;
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_default_priority to ucl_parser_add_chunk
  const char* ret_ucl_parser_get_cur_file_azeeu = ucl_parser_get_cur_file(parser);
  if (ret_ucl_parser_get_cur_file_azeeu == NULL){
  	return 0;
  }

  bool ret_ucl_parser_add_chunk_bjhxe = ucl_parser_add_chunk(parser, (const unsigned char *)data, (size_t )ret_ucl_parser_get_default_priority_gkkng);
  if (ret_ucl_parser_add_chunk_bjhxe == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  bool ret_ucl_parser_add_string_cfrcj = ucl_parser_add_string(parser, ret_ucl_copy_value_trash_imfem, (size_t )ret_ucl_parser_get_default_priority_gkkng);
  if (ret_ucl_parser_add_string_cfrcj == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}