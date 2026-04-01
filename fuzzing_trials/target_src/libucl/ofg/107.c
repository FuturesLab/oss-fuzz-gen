#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
  // Ensure that the input size is sufficient to create a valid ucl_object_t
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

  // Get the parsed UCL object
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj != NULL) {
    // Call the function-under-test
    ucl_type_t type = ucl_object_type(obj);
  }

  // Free the parser and the object
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}