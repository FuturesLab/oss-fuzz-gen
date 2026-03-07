#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Initialize a ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the root object from the parser
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function under test
    double result = ucl_object_todouble(root);

    // Optionally, perform some operations with the result
    (void)result; // Suppress unused variable warning
  }

  // Clean up
  ucl_parser_free(parser);

  return 0;
}