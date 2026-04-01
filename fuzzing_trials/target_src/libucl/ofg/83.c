#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>  // Include for the bool type

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
  // Ensure that the size is sufficient to create a valid ucl_object_t
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

  // Get the UCL object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj != NULL) {
    // Call the function under test
    bool result = ucl_object_toboolean(obj);
  }

  // Clean up
  ucl_parser_free(parser);

  return 0;
}