#include "ucl.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the input data
    char filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }
    close(fd);

    // Initialize the UCL parser
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