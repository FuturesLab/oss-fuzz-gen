#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Initialize a UCL parser
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
    const char *result = ucl_object_tostring(root);

    // Use the result to avoid compiler optimizations
    if (result != NULL) {
      size_t result_len = strlen(result);
      (void)result_len;
    }
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}