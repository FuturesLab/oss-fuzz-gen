#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
  // Create a new UCL parser instance
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0; // Return if parser creation fails
  }

  // Ensure that the data is not NULL and size is greater than 0
  if (data != NULL && size > 0) {
    // Call the function-under-test
    bool result = ucl_parser_insert_chunk(parser, data, size);

    // You can check the result if needed
    (void)result; // Suppress unused variable warning
  }

  // Free the UCL parser instance
  ucl_parser_free(parser);

  return 0;
}