#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_frombool

  ucl_object_t* ret_ucl_object_frombool_uuwtf = ucl_object_frombool(result);
  if (ret_ucl_object_frombool_uuwtf == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_frombool to ucl_array_size

  unsigned int ret_ucl_array_size_ylsot = ucl_array_size(ret_ucl_object_frombool_uuwtf);
  if (ret_ucl_array_size_ylsot < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}