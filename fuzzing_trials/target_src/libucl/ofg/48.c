#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
  // Ensure the input size is greater than 0
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

  // Get the root UCL object
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Prepare a variable to store the length of the string
  size_t len = 0;

  // Call the function-under-test
  const char *str = ucl_object_tolstring(obj, &len);

  // Free the parser and the object
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  // If str is not NULL, ensure to free it if necessary
  if (str != NULL) {
    // In some cases, ucl_object_tolstring might return a dynamically allocated
    // string, ensure to free it if that's the case.
    free((void *)str);
  }

  return 0;
}