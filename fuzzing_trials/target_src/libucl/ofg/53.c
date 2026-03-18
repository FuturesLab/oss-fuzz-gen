#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test
  const char *error = ucl_parser_get_error(parser);

  // Optionally, you can do something with the error message
  // For example, print it or check if it's NULL
  if (error != NULL) {
    // Handle the error message if needed
  }

  ucl_parser_free(parser);
  return 0;
}