#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
  // Ensure size is sufficient to extract a file path and priority
  if (size < sizeof(unsigned int) + 1) {
    return 0;
  }

  // Initialize the parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Extract the priority from the input data
  unsigned int priority = *(unsigned int *)data;

  // Extract the file path from the input data
  const char *file_path = (const char *)(data + sizeof(unsigned int));

  // Ensure the file path is null-terminated
  char *file_path_null_terminated = (char *)malloc(size - sizeof(unsigned int) + 1);
  if (file_path_null_terminated == NULL) {
    ucl_parser_free(parser);
    return 0;
  }
  memcpy(file_path_null_terminated, file_path, size - sizeof(unsigned int));
  file_path_null_terminated[size - sizeof(unsigned int)] = '\0';

  // Call the function under test
  bool result = ucl_parser_add_file_priority(parser, file_path_null_terminated, priority);

  // Clean up
  free(file_path_null_terminated);
  ucl_parser_free(parser);

  return 0;
}