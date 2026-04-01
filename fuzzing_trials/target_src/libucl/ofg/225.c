#include "ucl.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    int fd;
    bool result;

    // Create a temporary file
    fd = open("/tmp/fuzz_temp_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize the UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    result = ucl_parser_add_fd(parser, fd);

    // Clean up
    ucl_parser_free(parser);
    close(fd);
    unlink("/tmp/fuzz_temp_file");

    return 0;
}