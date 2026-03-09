#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
  // Ensure that the size is non-zero to avoid undefined behavior
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Call the function-under-test
  int priority = ucl_parser_get_default_priority(parser);

  // Free the parser
  ucl_parser_free(parser);

  // Return 0 to indicate successful execution
  return 0;
}