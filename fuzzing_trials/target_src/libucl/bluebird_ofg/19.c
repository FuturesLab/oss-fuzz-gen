#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
  // Create a new UCL parser

  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(-1);
  // End mutation: Producer.REPLACE_ARG_MUTATOR


  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_parser_register_macro
  FILE whstnejc;
  memset(&whstnejc, 0, sizeof(whstnejc));
  struct ucl_emitter_functions* ret_ucl_object_emit_file_funcs_vlpbh = ucl_object_emit_file_funcs(&whstnejc);
  if (ret_ucl_object_emit_file_funcs_vlpbh == NULL){
  	return 0;
  }

  bool ret_ucl_parser_register_macro_xtazv = ucl_parser_register_macro(parser, NULL, NULL, (void *)&whstnejc);
  if (ret_ucl_parser_register_macro_xtazv == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}