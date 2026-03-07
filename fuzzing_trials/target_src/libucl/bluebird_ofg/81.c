#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_add_chunk(parser, data, size);

  // Free the parser after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_add_string
  double ret_ucl_object_todouble_xdgwi = ucl_object_todouble(NULL);
  if (ret_ucl_object_todouble_xdgwi < 0){
  	return 0;
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_todouble to ucl_object_insert_key

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_todouble to ucl_parser_add_fd

  bool ret_ucl_parser_add_fd_ttoup = ucl_parser_add_fd(NULL, (int )ret_ucl_object_todouble_xdgwi);
  if (ret_ucl_parser_add_fd_ttoup == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_object_t* ret_ucl_object_fromdouble_gohhj = ucl_object_fromdouble(size);
  if (ret_ucl_object_fromdouble_gohhj == NULL){
  	return 0;
  }
  char *mwipyrfl[1024] = {"xccsu", NULL};
  struct ucl_emitter_functions* ret_ucl_object_emit_memory_funcs_qpgpe = ucl_object_emit_memory_funcs(mwipyrfl);
  if (ret_ucl_object_emit_memory_funcs_qpgpe == NULL){
  	return 0;
  }
  const ucl_object_t zptpeiqj;
  memset(&zptpeiqj, 0, sizeof(zptpeiqj));
  bool ret_ucl_object_toboolean_bzzuf = ucl_object_toboolean(&zptpeiqj);
  if (ret_ucl_object_toboolean_bzzuf == 0){
  	return 0;
  }

  bool ret_ucl_object_insert_key_glhry = ucl_object_insert_key(ret_ucl_object_fromdouble_gohhj, NULL, (const char *)*mwipyrfl, (size_t )ret_ucl_object_todouble_xdgwi, ret_ucl_object_toboolean_bzzuf);
  if (ret_ucl_object_insert_key_glhry == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  bool ret_ucl_parser_add_string_ffpnd = ucl_parser_add_string(parser, (const char *)"r", (size_t )ret_ucl_object_todouble_xdgwi);
  if (ret_ucl_parser_add_string_ffpnd == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string to ucl_object_iterate_with_error
  ucl_object_t blerndeu;
  memset(&blerndeu, 0, sizeof(blerndeu));
  ucl_object_t* ret_ucl_array_pop_last_fzvoq = ucl_array_pop_last(&blerndeu);
  if (ret_ucl_array_pop_last_fzvoq == NULL){
  	return 0;
  }
  ucl_object_iter_t feisybyp;
  memset(&feisybyp, 0, sizeof(feisybyp));
  bool ret_ucl_object_iter_chk_excpn_bnsdn = ucl_object_iter_chk_excpn(&feisybyp);
  if (ret_ucl_object_iter_chk_excpn_bnsdn == 0){
  	return 0;
  }
  int lrignxwz = 1;

  const ucl_object_t* ret_ucl_object_iterate_with_error_sdvcs = ucl_object_iterate_with_error(&blerndeu, &feisybyp, ret_ucl_parser_add_string_ffpnd, &lrignxwz);
  if (ret_ucl_object_iterate_with_error_sdvcs == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  // Return 0 as the function result is not needed for the fuzzer
  return 0;
}