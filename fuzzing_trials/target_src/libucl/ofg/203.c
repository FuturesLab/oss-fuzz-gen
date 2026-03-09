#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
  // Ensure the data is non-empty and null-terminated
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Convert the input data to a null-terminated string
  char *file_name = (char *)data;
  file_name[size - 1] = '\0';

  // Set a boolean value for the function call
  bool allow_override = true;

  // Call the function-under-test
  ucl_parser_set_filevars(parser, file_name, allow_override);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}