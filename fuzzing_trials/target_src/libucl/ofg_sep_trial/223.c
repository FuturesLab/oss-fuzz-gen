#include "ucl.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
  struct ucl_parser *parser;
  int fd;
  bool result;

  // Create a temporary file to use its file descriptor
  char filename[] = "/tmp/ucl_fuzz_XXXXXX";
  fd = mkstemp(filename);
  if (fd == -1) {
    return 0;
  }

  // Write the fuzzer data to the temporary file
  if (write(fd, data, size) != (ssize_t)size) {
    close(fd);
    unlink(filename);
    return 0;
  }

  // Reset the file offset to the beginning
  lseek(fd, 0, SEEK_SET);

  // Initialize the UCL parser
  parser = ucl_parser_new(0);
  if (parser == NULL) {
    close(fd);
    unlink(filename);
    return 0;
  }

  // Call the function-under-test
  result = ucl_parser_add_fd(parser, fd);

  // Clean up
  ucl_parser_free(parser);
  close(fd);
  unlink(filename);

  return 0;
}