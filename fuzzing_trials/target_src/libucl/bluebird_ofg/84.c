#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
  // Create a new UCL parser

  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(1);
  // End mutation: Producer.REPLACE_ARG_MUTATOR


  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_new to ucl_parser_register_variable
  char *kpnrzcuw[1024] = {"idtqh", NULL};
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_xthff = ucl_object_emit_memory_funcs(kpnrzcuw);
  if (ret_ucl_object_emit_memory_funcs_xthff == NULL){
  	return 0;
  }

  ucl_parser_register_variable(parser, (const char *)*kpnrzcuw, NULL);

  // End mutation: Producer.APPEND_MUTATOR

  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_clear_error

  ucl_parser_clear_error(parser);

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}