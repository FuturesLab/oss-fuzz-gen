#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
  // Ensure that size is sufficient to create a valid ucl_object_t
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

  // Get the parsed object
  const ucl_object_t *obj = ucl_parser_get_object(parser);

  // If the object is valid, call the function under test
  if (obj != NULL) {
    bool result = ucl_object_toboolean(obj);
  }

  // Free the parser and the parsed object
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}