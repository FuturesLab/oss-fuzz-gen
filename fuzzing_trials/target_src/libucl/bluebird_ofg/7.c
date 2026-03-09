#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_merge
  ucl_object_t* ret_ucl_object_typed_new_lhvdn = ucl_object_typed_new(0);
  if (ret_ucl_object_typed_new_lhvdn == NULL){
  	return 0;
  }
  const ucl_object_t qcgfkcvk;
  memset(&qcgfkcvk, 0, sizeof(qcgfkcvk));
  ucl_object_t* ret_ucl_object_copy_fnamu = ucl_object_copy(&qcgfkcvk);
  if (ret_ucl_object_copy_fnamu == NULL){
  	return 0;
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_copy to ucl_comments_add
  const ucl_object_t fpzynddi;
  memset(&fpzynddi, 0, sizeof(fpzynddi));
  ucl_object_t* ret_ucl_object_ref_urioc = ucl_object_ref(&fpzynddi);
  if (ret_ucl_object_ref_urioc == NULL){
  	return 0;
  }
  unsigned char ret_ucl_parser_chunk_peek_kyeib = ucl_parser_chunk_peek(NULL);

  ucl_comments_add(ret_ucl_object_copy_fnamu, ret_ucl_object_ref_urioc, (const char *)&ret_ucl_parser_chunk_peek_kyeib);

  // End mutation: Producer.APPEND_MUTATOR

  bool ret_ucl_object_merge_dmcfi = ucl_object_merge(ret_ucl_object_typed_new_lhvdn, ret_ucl_object_copy_fnamu, result);
  if (ret_ucl_object_merge_dmcfi == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_file
  char *jaaceftx[1024] = {"vykvq", NULL};
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_nacdh = ucl_object_emit_memory_funcs(jaaceftx);
  if (ret_ucl_object_emit_memory_funcs_nacdh == NULL){
  	return 0;
  }

  bool ret_ucl_parser_add_file_hjeba = ucl_parser_add_file(parser, (const char *)*jaaceftx);
  if (ret_ucl_parser_add_file_hjeba == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}