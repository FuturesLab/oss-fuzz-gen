#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
  // Initialize a ucl_parser and parse the input data
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Ensure the data is null-terminated for parsing
  char *null_terminated_data = (char *)malloc(size + 1);
  if (null_terminated_data == NULL) {
    ucl_parser_free(parser);
    return 0;
  }
  memcpy(null_terminated_data, data, size);
  null_terminated_data[size] = '\0';

  // Parse the data
  ucl_parser_add_string(parser, null_terminated_data, size);
  free(null_terminated_data);

  // Retrieve the root object
  ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj != NULL) {
    // Call the function-under-test
    ucl_object_t *popped_obj = ucl_array_pop_last(root_obj);
    
    // Free the popped object if it is not NULL
    if (popped_obj != NULL) {
      ucl_object_unref(popped_obj);
    }

    // Unref the root object
    ucl_object_unref(root_obj);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}