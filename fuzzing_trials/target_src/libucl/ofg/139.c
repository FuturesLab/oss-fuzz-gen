#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
  // Ensure that the size is non-zero for proper string handling
  if (size == 0) {
    return 0;
  }

  // Initialize a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Free the parser to test the function-under-test
  ucl_parser_free(parser);

  return 0;
}