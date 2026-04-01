#include "ucl.h"

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
  // Avoid calling with size 0
  if (size == 0) {
    return 0;
  }

  // Use the first byte of data to determine the integer parameter
  int param = (int)data[0];

  // Call the function-under-test
  struct ucl_parser *parser = ucl_parser_new(param);

  // Check if parser is not NULL
  if (parser != NULL) {
    // Perform additional operations if needed
    // ...

    // Free the parser
    ucl_parser_free(parser);
  }

  return 0;
}