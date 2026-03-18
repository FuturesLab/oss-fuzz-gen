#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
  // Ensure size is large enough to split into two non-empty strings
  if (size < 2) {
    return 0;
  }

  // Allocate memory for the parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Split the input data into two strings
  size_t var_name_len = size / 2;
  size_t var_value_len = size - var_name_len;

  char *var_name = (char *)malloc(var_name_len + 1);
  char *var_value = (char *)malloc(var_value_len + 1);

  if (var_name == NULL || var_value == NULL) {
    ucl_parser_free(parser);
    free(var_name);
    free(var_value);
    return 0;
  }

  memcpy(var_name, data, var_name_len);
  var_name[var_name_len] = '\0';

  memcpy(var_value, data + var_name_len, var_value_len);
  var_value[var_value_len] = '\0';

  // Call the function under test
  ucl_parser_register_variable(parser, var_name, var_value);

  // Clean up
  ucl_parser_free(parser);
  free(var_name);
  free(var_value);

  return 0;
}