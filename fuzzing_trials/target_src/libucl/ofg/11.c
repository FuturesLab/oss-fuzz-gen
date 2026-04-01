#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  const ucl_object_t *obj;
  const char *key;

  // Initialize a new UCL parser
  parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the parsed object
  obj = ucl_parser_get_object(parser);

  if (obj != NULL) {
    // Call the function under test
    key = ucl_object_key(obj);

    // Use the key in some way to avoid compiler optimizations
    if (key != NULL) {
      size_t key_len = strlen(key);
      if (key_len > 0) {
        volatile char first_char = key[0];
        (void)first_char;
      }
    }
  }

  // Free the UCL parser and object
  ucl_parser_free(parser);
  ucl_object_unref(obj);

  return 0;
}