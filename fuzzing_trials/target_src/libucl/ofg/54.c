#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
  // Ensure size is greater than 0 to avoid undefined behavior with empty input
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Call the function-under-test
  const char *error = ucl_parser_get_error(parser);

  // Use the error string to prevent any compiler optimizations removing the call
  if (error != NULL) {
    // You can print or log the error for debugging purposes if needed
    // printf("Error: %s\n", error);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}