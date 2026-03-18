#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with a non-null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  const ucl_object_t *obj;

  // Create a new UCL parser
  parser = ucl_parser_new(0);

  // Add the input data as a string to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Get the parsed object
  obj = ucl_parser_get_object(parser);

  // Call the function-under-test
  unsigned int array_size = ucl_array_size(obj);

  // Free the parser and the object
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}