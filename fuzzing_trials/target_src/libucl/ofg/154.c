#include "ucl.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    int fd;
    unsigned int priority;

    // Initialize the ucl_parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a temporary file to use its file descriptor
    fd = open("/tmp/fuzz_temp_file", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        ucl_parser_free(parser);
        return 0;
    }

    // Write the fuzzing data to the file
    if (write(fd, data, size) != size) {
        close(fd);
        ucl_parser_free(parser);
        return 0;
    }

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Use the first byte of data to determine priority, ensuring it is not zero
    priority = size > 0 ? data[0] : 1;

    // Call the function-under-test
    ucl_parser_add_fd_priority(parser, fd, priority);

    // Clean up
    close(fd);
    ucl_parser_free(parser);

    return 0;
}