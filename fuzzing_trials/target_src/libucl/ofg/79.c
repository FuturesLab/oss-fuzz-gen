#include "ucl.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
  // Ensure size is non-zero to avoid undefined behavior
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);

  // Call the function-under-test
  bool result = ucl_parser_insert_chunk(parser, data, size);

  // Free the parser
  ucl_parser_free(parser);

  return result;
}