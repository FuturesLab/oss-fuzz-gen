#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Get the UCL object from the parser
  ucl_object_t *obj = ucl_parser_get_object(parser);

  // Free the UCL object if it was created
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}