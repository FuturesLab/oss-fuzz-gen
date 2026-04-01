#include "ucl.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    int fd;
    unsigned int priority;

    // Create a temporary file to use its file descriptor
    char filename[] = "/tmp/ucl_fuzz_XXXXXX";
    fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize the parser
    parser = ucl_parser_new(0);

    // Set a non-zero priority for testing
    priority = 1;

    // Call the function under test
    ucl_parser_add_fd_priority(parser, fd, priority);

    // Clean up
    ucl_parser_free(parser);
    close(fd);
    unlink(filename);

    return 0;
}