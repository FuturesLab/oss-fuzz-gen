#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
  // Ensure that size is sufficient to extract an unsigned int for priority
  if (size < sizeof(unsigned int)) {
    return 0;
  }

  // Initialize a ucl_parser object
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Extract an unsigned int from the data for the priority
  unsigned int priority = *((unsigned int *)data);

  // Call the function under test
  bool result = ucl_parser_set_default_priority(parser, priority);

  // Clean up
  ucl_parser_free(parser);

  return 0;
}