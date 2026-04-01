#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file
    char filename[] = "/tmp/ucl_fuzz_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }
    close(fd);

    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    ucl_parser_add_file(parser, filename);

    // Clean up
    ucl_parser_free(parser);
    unlink(filename);

    return 0;
}