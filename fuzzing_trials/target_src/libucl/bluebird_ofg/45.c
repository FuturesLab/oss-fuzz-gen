#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_fd
  int ret_ucl_parser_get_error_code_lpulf = ucl_parser_get_error_code(parser);
  if (ret_ucl_parser_get_error_code_lpulf < 0){
  	return 0;
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_error_code to ucl_array_replace_index
  const ucl_object_t nlhfhdtv;
  memset(&nlhfhdtv, 0, sizeof(nlhfhdtv));
  ucl_object_t* ret_ucl_object_ref_ynvbs = ucl_object_ref(&nlhfhdtv);
  if (ret_ucl_object_ref_ynvbs == NULL){
  	return 0;
  }
  ucl_object_t* ret_ucl_object_new_szbxf = ucl_object_new();
  if (ret_ucl_object_new_szbxf == NULL){
  	return 0;
  }

  ucl_object_t* ret_ucl_array_replace_index_olrlq = ucl_array_replace_index(ret_ucl_object_ref_ynvbs, ret_ucl_object_new_szbxf, (unsigned int )ret_ucl_parser_get_error_code_lpulf);
  if (ret_ucl_array_replace_index_olrlq == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  bool ret_ucl_parser_add_fd_udlcu = ucl_parser_add_fd(parser, ret_ucl_parser_get_error_code_lpulf);
  if (ret_ucl_parser_add_fd_udlcu == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}