#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }


  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(size);
  // End mutation: Producer.REPLACE_ARG_MUTATOR


  if (parser == NULL) {
    return 0;
  }

  ucl_parser_add_string(parser, (char *)data, size);

  // Call the function-under-test
  unsigned char result = ucl_parser_chunk_peek(parser);

  // Clean up

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_free to ucl_parser_set_variables_handler
  const ucl_object_t* ret_ucl_parser_get_comments_qjafg = ucl_parser_get_comments(parser);
  if (ret_ucl_parser_get_comments_qjafg == NULL){
  	return 0;
  }

  ucl_parser_set_variables_handler(parser, NULL, (void *)parser);

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_free(parser);

  return 0;
}