#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
  // Ensure that size is not zero to prevent undefined behavior
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser instance
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Call the function-under-test
  int error_code = ucl_parser_get_error_code(parser);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}