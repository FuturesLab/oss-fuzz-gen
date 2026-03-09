#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
  struct ucl_parser *parser;
  char filename[] = "/tmp/ucl_fuzz_test_fileXXXXXX";
  int fd;
  FILE *file;

  // Create a temporary file
  fd = mkstemp(filename);
  if (fd == -1) {
    return 0;
  }

  // Write data to the temporary file
  file = fdopen(fd, "wb");
  if (file == NULL) {
    close(fd);
    unlink(filename);
    return 0;
  }

  fwrite(data, 1, size, file);
  fclose(file);

  // Initialize the parser
  parser = ucl_parser_new(0);
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