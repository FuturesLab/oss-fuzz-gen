#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
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

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_replace_key
  ucl_object_t ufplagxa;
  memset(&ufplagxa, 0, sizeof(ufplagxa));
  ucl_object_t sqvbtxqj;
  memset(&sqvbtxqj, 0, sizeof(sqvbtxqj));

  bool ret_ucl_object_replace_key_lwecm = ucl_object_replace_key(&ufplagxa, &sqvbtxqj, (const char *)"w", 0, result);
  if (ret_ucl_object_replace_key_lwecm == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  unsigned int ret_ucl_object_get_priority_fbawd = ucl_object_get_priority(NULL);
  if (ret_ucl_object_get_priority_fbawd < 0){
  	return 0;
  }
  unsigned int ret_ucl_parser_get_linenum_bglqv = ucl_parser_get_linenum(parser);
  if (ret_ucl_parser_get_linenum_bglqv < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_fd_priority_aoows = ucl_parser_add_fd_priority(parser, (int )ret_ucl_object_get_priority_fbawd, ret_ucl_parser_get_linenum_bglqv);
  if (ret_ucl_parser_add_fd_priority_aoows == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}