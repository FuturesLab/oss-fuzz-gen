#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
  // Ensure the input data is not empty
  if (size == 0) {
    return 0;
  }

  // Initialize a UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object from the parser
  const ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj != NULL) {
    // Call the function-under-test
    const char *key = ucl_object_key(root_obj);

    // Use the key in some way to prevent optimization out
    if (key != NULL && strlen(key) > 0) {
      // Do nothing, just ensure key is accessed
    }
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}