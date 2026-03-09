#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
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
  const ucl_object_t ljfhibwc;

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_iterate_safe
  const ucl_object_t nbbtbljt;
  memset(&nbbtbljt, 0, sizeof(nbbtbljt));
  ucl_object_iter_t ret_ucl_object_iterate_new_gdolk = ucl_object_iterate_new(&nbbtbljt);

  const ucl_object_t* ret_ucl_object_iterate_safe_jorqo = ucl_object_iterate_safe(ret_ucl_object_iterate_new_gdolk, result);
  if (ret_ucl_object_iterate_safe_jorqo == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  memset(&ljfhibwc, 0, sizeof(ljfhibwc));
  int64_t ret_ucl_object_toint_fdbkp = ucl_object_toint(&ljfhibwc);
  if (ret_ucl_object_toint_fdbkp < 0){
  	return 0;
  }
  unsigned int ret_ucl_parser_get_column_vnmji = ucl_parser_get_column(NULL);
  if (ret_ucl_parser_get_column_vnmji < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_fd_priority_tvnrm = ucl_parser_add_fd_priority(parser, (int )ret_ucl_object_toint_fdbkp, ret_ucl_parser_get_column_vnmji);
  if (ret_ucl_parser_add_fd_priority_tvnrm == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}