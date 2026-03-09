#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_chunk_priority
  unsigned char ret_ucl_parser_chunk_peek_rtivd = ucl_parser_chunk_peek(parser);
  int64_t ret_ucl_object_toint_zwjsf = ucl_object_toint(NULL);
  if (ret_ucl_object_toint_zwjsf < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_chunk_priority_fetyb = ucl_parser_add_chunk_priority(parser, &ret_ucl_parser_chunk_peek_rtivd, 1, (unsigned int )ret_ucl_object_toint_zwjsf);
  if (ret_ucl_parser_add_chunk_priority_fetyb == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}