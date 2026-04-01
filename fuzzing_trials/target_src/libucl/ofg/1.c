#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
  // Ensure the size is non-zero to avoid undefined behavior
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

  // Get the top object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Prepare a pointer to hold the string representation
  const char *str_rep = NULL;

  // Call the function-under-test
  bool result = ucl_object_tostring_safe(obj, &str_rep);

  // Clean up
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}