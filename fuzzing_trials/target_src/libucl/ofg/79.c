#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Prepare a size_t variable to receive the length of the key
    size_t key_length = 0;

    // Call the function-under-test
    const char *key = ucl_object_keyl(root, &key_length);

    // Use the key and key_length in some way to avoid compiler warnings
    if (key != NULL && key_length > 0) {
      // Just a dummy operation to use the key and key_length
      (void)strnlen(key, key_length);
    }
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}