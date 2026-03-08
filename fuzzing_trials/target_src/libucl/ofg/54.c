#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
  if (size < sizeof(unsigned int)) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  unsigned int priority = *(unsigned int *)data;

  // Call the function-under-test
  bool result = ucl_parser_set_default_priority(parser, priority);

  // Clean up
  ucl_parser_free(parser);

  return 0;
}