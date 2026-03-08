#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Call the function-under-test
  bool result = ucl_parser_insert_chunk(parser, data, size);

  // Clean up
  ucl_parser_free(parser);

  return 0;
}