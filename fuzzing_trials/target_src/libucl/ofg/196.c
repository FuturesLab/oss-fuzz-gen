#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
  // Ensure the size is non-zero for valid input
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test
  unsigned int column = ucl_parser_get_column(parser);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}