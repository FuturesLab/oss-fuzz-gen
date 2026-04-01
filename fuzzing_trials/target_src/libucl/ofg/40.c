#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
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
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    int64_t result = ucl_object_toint(root);
  }

  // Free the parser and its objects
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}