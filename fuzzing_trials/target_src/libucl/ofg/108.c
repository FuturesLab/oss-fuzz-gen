#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Parse the input data
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);

  if (root != NULL) {
    // Call the function-under-test
    ucl_type_t type = ucl_object_type(root);
  }

  // Clean up
  ucl_parser_free(parser);
  return 0;
}