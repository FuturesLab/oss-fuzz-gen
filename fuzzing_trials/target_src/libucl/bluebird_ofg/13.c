#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
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

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_get_error


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_parser_insert_chunk
  char iijkofbm[1024] = "ibfcs";

  bool ret_ucl_parser_insert_chunk_mmbdz = ucl_parser_insert_chunk(parser, iijkofbm, UCL_PRIORITY_MAX);
  if (ret_ucl_parser_insert_chunk_mmbdz == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  const char* ret_ucl_parser_get_error_xxxcg = ucl_parser_get_error(parser);
  if (ret_ucl_parser_get_error_xxxcg == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_string
  char* ret_ucl_copy_value_trash_iqvds = ucl_copy_value_trash(NULL);
  if (ret_ucl_copy_value_trash_iqvds == NULL){
  	return 0;
  }
  unsigned int ret_ucl_parser_get_linenum_yfbwb = ucl_parser_get_linenum(parser);
  if (ret_ucl_parser_get_linenum_yfbwb < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_string_ikvff = ucl_parser_add_string(parser, ret_ucl_copy_value_trash_iqvds, (size_t )ret_ucl_parser_get_linenum_yfbwb);
  if (ret_ucl_parser_add_string_ikvff == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}