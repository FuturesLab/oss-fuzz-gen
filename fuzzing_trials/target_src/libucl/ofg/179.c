#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
  // If size is 0, there's no data to process
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test
  int priority = ucl_parser_get_default_priority(parser);

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}