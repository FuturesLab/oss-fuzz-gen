#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
  // Ensure size is sufficient to create a non-empty string
  if (size == 0) {
    return 0;
  }

  // Create a null-terminated string from the data
  char *file_name = (char *)malloc(size + 1);
  if (file_name == NULL) {
    return 0;
  }
  memcpy(file_name, data, size);
  file_name[size] = '\0';

  // Initialize the parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    free(file_name);
    return 0;
  }

  // Use a fixed priority for fuzzing
  unsigned int priority = 1;

  // Call the function under test
  ucl_parser_add_file_priority(parser, file_name, priority);

  // Clean up
  ucl_parser_free(parser);
  free(file_name);

  return 0;
}