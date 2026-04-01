#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Call the function-under-test
  bool result = ucl_parser_add_string(parser, (const char *)data, size);

  // Free the parser after use
  ucl_parser_free(parser);

  return 0;
}