#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
  // Initialize the parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    const ucl_object_t *head = ucl_array_head(root);

    // Perform any additional operations on the head if needed
    (void)head; // Suppress unused variable warning
  }

  // Clean up
  ucl_parser_free(parser);

  return 0;
}