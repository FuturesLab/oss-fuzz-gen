#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
  // Ensure that size is non-zero to safely read an integer
  if (size < sizeof(int)) {
    return 0;
  }

  // Interpret the first 4 bytes of data as an integer
  int flags = *(const int *)data;

  // Call the function-under-test
  struct ucl_parser *parser = ucl_parser_new(flags);

  // Free the parser if it was successfully created
  if (parser != NULL) {
    ucl_parser_free(parser);
  }

  return 0;
}