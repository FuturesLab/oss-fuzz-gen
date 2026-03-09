#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
  // Ensure the data is not empty
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the root object from the parser
  ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj != NULL) {
    // Call the function-under-test
    ucl_object_t *ref_obj = ucl_object_ref(root_obj);

    // Decrease the reference count for the referenced object
    ucl_object_unref(ref_obj);

    // Unref the root object
    ucl_object_unref(root_obj);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}