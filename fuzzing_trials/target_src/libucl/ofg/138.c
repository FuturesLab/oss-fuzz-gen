#include "ucl.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Initialize a ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the UCL object
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Prepare a boolean variable to store the result
  _Bool result = false;

  // Call the function-under-test
  ucl_object_toboolean_safe(obj, &result);

  // Clean up
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}