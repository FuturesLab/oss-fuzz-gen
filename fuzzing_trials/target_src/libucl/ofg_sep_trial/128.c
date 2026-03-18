#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
  // Ensure that the input size is sufficient for a null-terminated string
  if (size == 0) {
    return 0;
  }

  // Create a ucl_parser object
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object from the parser
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Ensure the key is null-terminated
  char key[size + 1];
  memcpy(key, data, size);
  key[size] = '\0';

  // Call the function-under-test
  const ucl_object_t *result = ucl_object_lookup(root, key);

  // Clean up
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}