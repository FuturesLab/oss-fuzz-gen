#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
  // Create a temporary file to write the input data
  char filename[] = "/tmp/ucl_fuzz_XXXXXX";
  int fd = mkstemp(filename);
  if (fd == -1) {
    return 0;
  }

  // Write the input data to the file
  if (write(fd, data, size) != (ssize_t)size) {
    close(fd);
    unlink(filename);
    return 0;
  }

  // Close the file descriptor
  close(fd);

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    unlink(filename);
    return 0;
  }

  // Call the function under test
  ucl_parser_add_file(parser, filename);

  // Clean up
  ucl_parser_free(parser);
  unlink(filename);

  return 0;
}