#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
  // Ensure the size is greater than 0 to create a valid string
  if (size == 0) {
    return 0;
  }

  // Create a null-terminated string from the input data
  char *input_str = (char *)malloc(size + 1);
  if (input_str == NULL) {
    return 0;
  }
  memcpy(input_str, data, size);
  input_str[size] = '\0';

  // Create a UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    free(input_str);
    return 0;
  }

  // Add the string to the parser
  if (!ucl_parser_add_string(parser, input_str, size)) {
    ucl_parser_free(parser);
    free(input_str);
    return 0;
  }

  // Get the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function under test
    double result = ucl_object_todouble(root);
    (void)result; // Use the result to avoid unused variable warning
  }

  // Clean up
  ucl_object_unref(root);
  ucl_parser_free(parser);
  free(input_str);

  return 0;
}