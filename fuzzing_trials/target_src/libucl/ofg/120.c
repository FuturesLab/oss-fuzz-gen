#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the root object from the parser
  const ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  ucl_object_t *ref_obj = ucl_object_ref(root_obj);

  // Clean up
  if (ref_obj != NULL) {
    ucl_object_unref(ref_obj);
  }
  ucl_parser_free(parser);

  return 0;
}