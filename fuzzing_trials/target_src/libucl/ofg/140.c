#include <stddef.h>
#include <stdint.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
  // Ensure size is non-zero to avoid undefined behavior with non-null-terminated strings
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Free the UCL parser
  ucl_parser_free(parser);

  return 0;
}