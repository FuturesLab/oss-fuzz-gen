#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
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
  int ret_ucl_parser_get_error_code_bwyka = ucl_parser_get_error_code(NULL);
  if (ret_ucl_parser_get_error_code_bwyka < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_fd_priority_cmazz = ucl_parser_add_fd_priority(parser, 0, (unsigned int )ret_ucl_parser_get_error_code_bwyka);
  if (ret_ucl_parser_add_fd_priority_cmazz == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}