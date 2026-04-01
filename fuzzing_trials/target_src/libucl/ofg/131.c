#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
  // Ensure that the input size is sufficient to split into two strings
  if (size < 2) {
    return 0;
  }

  // Initialize the UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Split the input data into two non-null strings
  size_t mid = size / 2;
  char *variable_name = (char *)data;
  char *variable_value = (char *)(data + mid);

  // Ensure both strings are null-terminated
  variable_name[mid - 1] = '\0';
  variable_value[size - mid - 1] = '\0';

  // Call the function under test
  ucl_parser_register_variable(parser, variable_name, variable_value);

  // Free the UCL parser
  ucl_parser_free(parser);

  return 0;
}