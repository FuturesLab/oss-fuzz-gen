#include "ucl.h"
#include <fcntl.h>
#include "unistd.h"
#include <stdbool.h>
#include <stdint.h>
#include "stdio.h"

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzzing data
    char filename[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Reset the file descriptor offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Call the function under test
    ucl_parser_add_fd(parser, fd);

    // Clean up
    ucl_parser_free(parser);
    close(fd);
    unlink(filename);

    return 0;
}