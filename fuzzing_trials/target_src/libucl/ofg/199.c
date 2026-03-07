#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
  // Initialize a ucl_parser and parse the input data
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Ensure the data is null-terminated for parsing
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    ucl_parser_free(parser);
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Add the null-terminated string to the parser
  if (!ucl_parser_add_string(parser, input_data, size)) {
    free(input_data);
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj != NULL) {
    // Call the function-under-test
    const char *result = ucl_object_tostring_forced(obj);
    // Use the result in some way to avoid compiler optimizations ignoring it
    if (result != NULL) {
      // Print the result for debugging purposes (optional)
      // printf("Result: %s\n", result);
    }
  }

  // Clean up
  free(input_data);
  ucl_parser_free(parser);

  return 0;
}