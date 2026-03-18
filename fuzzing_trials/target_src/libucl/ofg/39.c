#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
  // Ensure the input size is sufficient to create a ucl_object_t
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj != NULL) {
    // Call the function-under-test
    int64_t result = ucl_object_toint(obj);
    (void)result; // Suppress unused variable warning
  }

  // Free the parser and its resources
  ucl_parser_free(parser);

  return 0;
}