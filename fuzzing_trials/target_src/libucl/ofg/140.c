#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
  // Initialize the parser
  struct ucl_parser *parser = ucl_parser_new(0);

  // Check if parser was created successfully
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}