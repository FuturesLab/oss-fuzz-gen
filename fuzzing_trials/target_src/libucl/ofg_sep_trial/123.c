#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
  // Initialize the parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  if (size > 0 && ucl_parser_add_chunk(parser, data, size) == false) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root object
  const ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  const ucl_object_t *tail_obj = ucl_array_tail(root_obj);

  // Clean up
  ucl_object_unref(root_obj);
  ucl_parser_free(parser);

  return 0;
}