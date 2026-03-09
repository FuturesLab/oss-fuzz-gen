#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    int fd;
    unsigned int priority;
    
    // Create a new UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a temporary file and write the data to it
    fd = open("/tmp/fuzz_temp_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        ucl_parser_free(parser);
        return 0;
    }

    write(fd, data, size);
    lseek(fd, 0, SEEK_SET);

    // Set a priority value (try different values)
    priority = 1;

    // Call the function under test
    ucl_parser_add_fd_priority(parser, fd, priority);

    // Clean up
    close(fd);
    ucl_parser_free(parser);

    return 0;
}