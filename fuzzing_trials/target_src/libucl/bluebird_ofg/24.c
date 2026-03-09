#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We dont null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }
  
  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  ucl_parser_add_string(parser, (char *)data, size);

  if (ucl_parser_get_error(parser) != NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_error to ucl_parser_add_special_handler
  struct ucl_parser_special_handler pedbuawu;
  memset(&pedbuawu, 0, sizeof(pedbuawu));

  ucl_parser_add_special_handler(parser, &pedbuawu);

  // End mutation: Producer.APPEND_MUTATOR

  ucl_parser_chunk_skip(parser);

  ucl_parser_free(parser);
  return 0;
}