#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Clear any errors that might have occurred
  ucl_parser_clear_error(parser);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}