#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Retrieve the root object
  ucl_object_t *root = ucl_parser_get_object(parser);

  if (root != NULL) {
    // Call the function under test
    ucl_object_t *popped_object = ucl_array_pop_first(root);

    // Free the popped object if it exists
    if (popped_object != NULL) {
      ucl_object_unref(popped_object);
    }

    // Unreference the root object
    ucl_object_unref(root);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}