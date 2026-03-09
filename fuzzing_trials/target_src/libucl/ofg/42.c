#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
  // Ensure size is non-zero for valid parsing
  if (size == 0) {
    return 0;
  }

  // Create a UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Parse the input data
  ucl_parser_add_chunk(parser, data, size);

  // Get the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    int64_t result = ucl_object_toint(root);
    (void)result; // Suppress unused variable warning
  }

  // Clean up
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}