#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
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
  unsigned int ret_ucl_object_get_priority_fbawd = ucl_object_get_priority(NULL);
  if (ret_ucl_object_get_priority_fbawd < 0){
  	return 0;
  }

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_get_priority to ucl_object_insert_key_merged
  ucl_object_t* ret_ucl_object_typed_new_wrect = ucl_object_typed_new(0);
  if (ret_ucl_object_typed_new_wrect == NULL){
  	return 0;
  }
  const ucl_object_t sfxkytvs;
  memset(&sfxkytvs, 0, sizeof(sfxkytvs));
  ucl_object_t* ret_ucl_object_copy_asqrr = ucl_object_copy(&sfxkytvs);
  if (ret_ucl_object_copy_asqrr == NULL){
  	return 0;
  }
  char *ywobrcdi[1024] = {"pntym", NULL};
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_qzxqo = ucl_object_emit_memory_funcs(ywobrcdi);
  if (ret_ucl_object_emit_memory_funcs_qzxqo == NULL){
  	return 0;
  }

  bool ret_ucl_object_insert_key_merged_yjjpm = ucl_object_insert_key_merged(ret_ucl_object_typed_new_wrect, ret_ucl_object_copy_asqrr, (const char *)*ywobrcdi, (size_t )ret_ucl_object_get_priority_fbawd, 0);
  if (ret_ucl_object_insert_key_merged_yjjpm == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

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