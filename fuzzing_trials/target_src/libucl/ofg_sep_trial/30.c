#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
  // Ensure the data is not empty
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Ensure the data is null-terminated for safe string operations
  char *null_terminated_data = (char *)malloc(size + 1);
  if (null_terminated_data == NULL) {
    ucl_parser_free(parser);
    return 0;
  }
  memcpy(null_terminated_data, data, size);
  null_terminated_data[size] = '\0';

  // Call the function-under-test
  ucl_parser_add_string(parser, null_terminated_data, size);

  // Clean up
  free(null_terminated_data);
  ucl_parser_free(parser);

  return 0;
}