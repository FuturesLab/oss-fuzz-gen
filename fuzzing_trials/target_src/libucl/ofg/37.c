#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
  // Ensure there is enough data to split for key and value
  if (size < 2) {
    return 0;
  }

  // Initialize a ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the top object from the parser
  ucl_object_t *top_obj = ucl_parser_get_object(parser);

  // Ensure top_obj is not NULL
  if (top_obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Use the first byte of data as the length of the key
  size_t key_len = data[0] % size;
  if (key_len == 0) {
    key_len = 1; // Ensure key length is at least 1
  }

  // Extract the key from the data
  char key[key_len + 1];
  memcpy(key, data + 1, key_len);
  key[key_len] = '\0'; // Null-terminate the key

  // Call the function-under-test
  ucl_object_t *popped_obj = ucl_object_pop_key(top_obj, key);

  // Free the popped object if it exists
  if (popped_obj != NULL) {
    ucl_object_unref(popped_obj);
  }

  // Clean up
  ucl_object_unref(top_obj);
  ucl_parser_free(parser);

  return 0;
}