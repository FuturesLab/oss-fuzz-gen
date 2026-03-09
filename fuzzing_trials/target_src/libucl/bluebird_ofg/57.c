#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_chunk to ucl_object_merge
  ucl_object_t* ret_ucl_object_typed_new_myqti = ucl_object_typed_new(0);
  if (ret_ucl_object_typed_new_myqti == NULL){
  	return 0;
  }
  ucl_object_t azdgdasy;

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_typed_new to ucl_object_key


  // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ucl_object_key with ucl_object_tostring
  const char* ret_ucl_object_key_djuwg = ucl_object_tostring(ret_ucl_object_typed_new_myqti);
  // End mutation: Producer.REPLACE_FUNC_MUTATOR


  if (ret_ucl_object_key_djuwg == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  memset(&azdgdasy, 0, sizeof(azdgdasy));

  bool ret_ucl_object_merge_zefko = ucl_object_merge(&azdgdasy, ret_ucl_object_typed_new_myqti, result);
  if (ret_ucl_object_merge_zefko == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}