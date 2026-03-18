#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
  // Ensure size is not zero to avoid undefined behavior with non-null-terminated strings
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test
  unsigned int line_number = ucl_parser_get_linenum(parser);

  // Use the result to prevent compiler optimizations that remove the call
  if (line_number == 0) {
    // Do something trivial
  }

  ucl_parser_free(parser);
  return 0;
}