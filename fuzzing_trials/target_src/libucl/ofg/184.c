#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
  // If size is 0, we cannot create a valid string, so return early
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object from the parser
  ucl_object_t *root_obj = ucl_parser_get_object(parser);

  // Free the parser
  ucl_parser_free(parser);

  // If a root object was successfully created, unref it
  if (root_obj != NULL) {
    ucl_object_unref(root_obj);
  }

  return 0;
}