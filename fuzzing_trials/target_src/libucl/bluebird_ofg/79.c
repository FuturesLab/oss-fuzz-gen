#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
  // Create a new UCL parser

  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(UCL_PRIORITY_MAX);
  // End mutation: Producer.REPLACE_ARG_MUTATOR


  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_parser_add_fd_priority
  unsigned int ret_ucl_object_get_priority_cvloz = ucl_object_get_priority(NULL);
  if (ret_ucl_object_get_priority_cvloz < 0){
  	return 0;
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_get_priority to ucl_parser_add_string_priority
  const ucl_object_t byazzsya;
  memset(&byazzsya, 0, sizeof(byazzsya));
  char* ret_ucl_copy_value_trash_wpsbh = ucl_copy_value_trash(&byazzsya);
  if (ret_ucl_copy_value_trash_wpsbh == NULL){
  	return 0;
  }

  bool ret_ucl_parser_add_string_priority_wmqvu = ucl_parser_add_string_priority(NULL, ret_ucl_copy_value_trash_wpsbh, (size_t )ret_ucl_object_get_priority_cvloz, UCL_PRIORITY_MAX);
  if (ret_ucl_parser_add_string_priority_wmqvu == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  bool ret_ucl_parser_add_fd_priority_gwcpr = ucl_parser_add_fd_priority(parser, 1, ret_ucl_object_get_priority_cvloz);
  if (ret_ucl_parser_add_fd_priority_gwcpr == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}