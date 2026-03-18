#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  // Add the input data to the parser
  ucl_parser_add_string(parser, (char *)data, size);

  // Call the function-under-test
  const char *cur_file = ucl_parser_get_cur_file(parser);

  // Check the result (cur_file can be NULL if no file is associated)
  if (cur_file != NULL) {
    // Do something with cur_file if needed, for now, just ensure it's called
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}