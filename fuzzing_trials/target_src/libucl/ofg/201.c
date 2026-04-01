#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
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
  const ucl_object_t *root_obj = ucl_parser_get_object(parser);
  if (root_obj != NULL) {
    // Call the function-under-test
    const char *result = ucl_object_tostring_forced(root_obj);
    (void)result; // Use result to avoid unused variable warning
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}