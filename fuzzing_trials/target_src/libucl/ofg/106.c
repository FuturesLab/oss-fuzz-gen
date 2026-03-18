#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  if (!ucl_parser_add_string(parser, (const char *)data, size)) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root object from the parser
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  ucl_object_t *copy = ucl_object_copy(root);

  // Clean up
  ucl_object_unref(copy);
  ucl_parser_free(parser);

  return 0;
}