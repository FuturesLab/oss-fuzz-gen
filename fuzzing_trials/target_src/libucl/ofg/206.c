#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
  struct ucl_parser *parser;
  char *filename;
  bool ret;

  // Ensure size is sufficient to create a non-empty filename
  if (size == 0) {
    return 0;
  }

  // Allocate memory for the filename and ensure null-termination
  filename = (char *)malloc(size + 1);
  if (filename == NULL) {
    return 0;
  }
  memcpy(filename, data, size);
  filename[size] = '\0';

  // Create a new UCL parser
  parser = ucl_parser_new(0);
  if (parser == NULL) {
    free(filename);
    return 0;
  }

  // Call the function under test
  ret = ucl_parser_set_filevars(parser, filename, true);

  // Clean up
  ucl_parser_free(parser);
  free(filename);

  return 0;
}