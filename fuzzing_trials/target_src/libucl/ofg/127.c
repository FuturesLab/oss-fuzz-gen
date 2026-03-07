#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Ensure the input data is null-terminated
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    ucl_parser_free(parser);
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input data
  ucl_parser_add_string(parser, input_data, size);

  // Get the root UCL object
  ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    ucl_object_t *popped_object = ucl_array_pop_last(root);
    
    // Clean up the popped object
    if (popped_object != NULL) {
      ucl_object_unref(popped_object);
    }
    
    // Clean up the root object
    ucl_object_unref(root);
  }

  // Clean up
  free(input_data);
  ucl_parser_free(parser);

  return 0;
}