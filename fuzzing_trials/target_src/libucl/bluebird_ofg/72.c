#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_parser_add_chunk_full
  char* ret_ucl_copy_key_trash_vlhoe = ucl_copy_key_trash(NULL);
  if (ret_ucl_copy_key_trash_vlhoe == NULL){
  	return 0;
  }
  int64_t ret_ucl_object_toint_omfnq = ucl_object_toint(NULL);
  if (ret_ucl_object_toint_omfnq < 0){
  	return 0;
  }
  int ret_ucl_parser_get_error_code_lcvlx = ucl_parser_get_error_code(parser);
  if (ret_ucl_parser_get_error_code_lcvlx < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_chunk_full_avsya = ucl_parser_add_chunk_full(parser, (const unsigned char *)ret_ucl_copy_key_trash_vlhoe, (size_t )ret_ucl_object_toint_omfnq, (unsigned int )ret_ucl_parser_get_error_code_lcvlx, 0, 0);
  if (ret_ucl_parser_add_chunk_full_avsya == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}