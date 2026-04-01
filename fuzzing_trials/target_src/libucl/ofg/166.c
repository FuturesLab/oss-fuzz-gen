#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
  // If size is 0, there's nothing to process
  if (size == 0) {
    return 0;
  }

  // Initialize a UCL parser
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

  // Call the function under test
  char *copied_value = ucl_copy_value_trash(root_obj);

  // Free the copied value if it was successfully allocated
  if (copied_value != NULL) {
    free(copied_value);
  }

  // Clean up
  ucl_object_unref(root_obj);
  ucl_parser_free(parser);

  return 0;
}