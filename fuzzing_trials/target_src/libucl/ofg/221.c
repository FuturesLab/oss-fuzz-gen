#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
  // Initialize the ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Create a ucl_object_t from the input data
  ucl_object_t *obj = ucl_object_fromstring_common((const char *)data, size, 0);
  if (obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_set_include_path(parser, obj);

  // Clean up
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}