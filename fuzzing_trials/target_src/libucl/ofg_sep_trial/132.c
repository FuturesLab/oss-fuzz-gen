#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  // Initialize the ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Split the input data into two non-null strings
  size_t len1 = data[0] % size; // Length of the first string
  size_t len2 = size - len1 - 1; // Length of the second string

  char *var_name = (char *)malloc(len1 + 1);
  char *var_value = (char *)malloc(len2 + 1);

  if (var_name == NULL || var_value == NULL) {
    ucl_parser_free(parser);
    free(var_name);
    free(var_value);
    return 0;
  }

  memcpy(var_name, data + 1, len1);
  var_name[len1] = '\0';

  memcpy(var_value, data + 1 + len1, len2);
  var_value[len2] = '\0';

  // Call the function-under-test
  ucl_parser_register_variable(parser, var_name, var_value);

  // Clean up
  ucl_parser_free(parser);
  free(var_name);
  free(var_value);

  return 0;
}