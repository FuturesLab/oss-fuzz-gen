#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  ucl_object_t *obj = NULL;
  ucl_object_t *copy = NULL;

  parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Get the parsed object
  obj = ucl_parser_get_object(parser);

  if (obj != NULL) {
    // Call the function-under-test
    copy = ucl_object_copy(obj);

    // Clean up the copied object
    if (copy != NULL) {
      ucl_object_unref(copy);
    }

    // Clean up the original object
    ucl_object_unref(obj);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}