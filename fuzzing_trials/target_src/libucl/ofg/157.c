#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the root object
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj != NULL) {
    // Call the function-under-test
    const char *str = ucl_object_tostring(obj);

    // Use the result (str) in some way to avoid compiler optimizations
    if (str != NULL) {
      size_t len = strlen(str);
      volatile char dummy = str[len > 0 ? len - 1 : 0];
      (void)dummy;
    }
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}