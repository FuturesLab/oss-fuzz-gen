#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
  // Ensure the input size is not zero to avoid undefined behavior
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test
  ucl_object_t *obj = ucl_parser_get_object(parser);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }
  ucl_parser_free(parser);

  return 0;
}