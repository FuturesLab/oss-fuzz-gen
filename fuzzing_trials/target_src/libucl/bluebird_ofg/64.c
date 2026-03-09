#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_register_context_macro
  struct ucl_emitter_functions* ret_ucl_object_emit_fd_funcs_zycyg = ucl_object_emit_fd_funcs(64);
  if (ret_ucl_object_emit_fd_funcs_zycyg == NULL){
  	return 0;
  }

  bool ret_ucl_parser_register_context_macro_zzpdc = ucl_parser_register_context_macro(parser, (const char *)"w", NULL, (void *)ret_ucl_object_emit_fd_funcs_zycyg);
  if (ret_ucl_parser_register_context_macro_zzpdc == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}