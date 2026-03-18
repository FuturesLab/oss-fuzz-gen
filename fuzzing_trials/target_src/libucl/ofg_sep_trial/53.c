#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
  // Ensure there's enough data to extract an unsigned int
  if (size < sizeof(unsigned int)) {
    return 0;
  }

  // Initialize the ucl_parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Extract an unsigned int from the input data
  unsigned int priority = *(const unsigned int *)data;

  // Call the function-under-test
  bool result = ucl_parser_set_default_priority(parser, priority);

  // Clean up
  ucl_parser_free(parser);

  return 0;
}