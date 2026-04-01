#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
  // Ensure the size is sufficient to extract an integer
  if (size < sizeof(int)) {
    return 0;
  }

  // Extract an integer from the data
  int option = *(const int *)data;

  // Call the function-under-test
  struct ucl_parser *parser = ucl_parser_new(option);

  // Clean up by freeing the parser if it was successfully created
  if (parser != NULL) {
    ucl_parser_free(parser);
  }

  return 0;
}