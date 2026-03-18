#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
  // Initialize a UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  if (size > 0) {
    ucl_parser_add_chunk(parser, data, size);
  }

  // Get the root UCL object
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root != NULL) {
    // Call the function-under-test
    const char *key = ucl_object_key(root);

    // Use the key in some way to avoid compiler optimizations removing the call
    if (key != NULL) {
      size_t key_len = strlen(key);
      if (key_len > 0) {
        // Do something trivial with the key
        volatile char first_char = key[0];
        (void)first_char;
      }
    }
  }

  // Free the UCL parser
  ucl_parser_free(parser);

  return 0;
}