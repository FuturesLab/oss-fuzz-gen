#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
  // Ensure size is non-zero for valid string input
  if (size == 0) {
    return 0;
  }

  // Initialize a UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data as a string to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Retrieve the current file name, if any
  const char *cur_file = ucl_parser_get_cur_file(parser);

  // Use the retrieved file name in some way, here we just check if it's not NULL
  if (cur_file != NULL) {
    // Do something with cur_file if needed
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}