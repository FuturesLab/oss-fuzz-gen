#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_new to ucl_parser_set_include_tracer
  char *lieosnnx[1024] = {"ldapj", NULL};
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_ugoxl = ucl_object_emit_memory_funcs(lieosnnx);
  if (ret_ucl_object_emit_memory_funcs_ugoxl == NULL){
  	return 0;
  }

  ucl_parser_set_include_tracer(parser, NULL, (void *)ret_ucl_object_emit_memory_funcs_ugoxl);

  // End mutation: Producer.APPEND_MUTATOR

  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_chunk_priority
  unsigned int ret_ucl_parser_get_column_yhken = ucl_parser_get_column(parser);
  if (ret_ucl_parser_get_column_yhken < 0){
  	return 0;
  }
  int ret_ucl_parser_get_default_priority_wyeou = ucl_parser_get_default_priority(NULL);
  if (ret_ucl_parser_get_default_priority_wyeou < 0){
  	return 0;
  }

  bool ret_ucl_parser_add_chunk_priority_anwnm = ucl_parser_add_chunk_priority(parser, (const unsigned char *)*lieosnnx, (size_t )ret_ucl_parser_get_column_yhken, (unsigned int )ret_ucl_parser_get_default_priority_wyeou);
  if (ret_ucl_parser_add_chunk_priority_anwnm == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}