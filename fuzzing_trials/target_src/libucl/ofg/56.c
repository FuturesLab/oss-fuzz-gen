#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
  // Ensure size is non-zero for valid string input
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Retrieve the error message, if any
  const char *error_msg = ucl_parser_get_error(parser);

  // Use the error message in some way to ensure it is accessed
  if (error_msg != NULL) {
    // For example, we can print it or just access it to ensure it's used
    volatile const char *access_error = error_msg;
    (void)access_error;
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}