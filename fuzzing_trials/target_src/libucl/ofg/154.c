#include "ucl.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
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

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Set a non-zero priority
    unsigned int priority = 1;

    // Call the function under test
    ucl_parser_add_fd_priority(parser, fd, priority);

    // Clean up
    ucl_parser_free(parser);
    close(fd);
    unlink(filename);

    return 0;
}