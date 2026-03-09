#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
  // Create a ucl_parser object
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  if (size > 0) {
    ucl_parser_add_chunk(parser, data, size);
  }

  // Get the root object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);

  // Call the function-under-test
  if (obj != NULL) {
    const char *str = ucl_object_tostring(obj);
    if (str != NULL) {
      // Do something with the resulting string if needed
      // For now, just suppress unused variable warning
      (void)str;
    }
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}