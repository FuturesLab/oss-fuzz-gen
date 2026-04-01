#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
  // Ensure size is sufficient to create a ucl_object_t
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Retrieve the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    double result = ucl_object_todouble(root);
  }

  // Free the parser and UCL object
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}