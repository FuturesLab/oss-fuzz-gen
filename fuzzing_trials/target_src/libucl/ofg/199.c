#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
  // Ensure the data is not empty
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Call the function-under-test
  unsigned int column = ucl_parser_get_column(parser);

  // Use the column value to avoid unused variable warning
  if (column > 0) {
    // Do something trivial with the column value
    column = column;
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}