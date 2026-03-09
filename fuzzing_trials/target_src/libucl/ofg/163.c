#include <stdint.h>
#include <stdbool.h>
#include <ucl.h>
#include <unistd.h> // For close()

int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a temporary file to simulate a file descriptor with the input data
    int fd = fileno(tmpfile());
    if (fd == -1) {
        ucl_parser_free(parser);
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        ucl_parser_free(parser);
        return 0;
    }

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Prepare the options and enumeration types
    unsigned int options = 0; // No specific options
    enum ucl_duplicate_strategy dup_strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;

    // Call the function-under-test
    bool result = ucl_parser_add_fd_full(parser, fd, options, dup_strategy, parse_type);

    // Clean up
    close(fd);
    ucl_parser_free(parser);

    return result ? 1 : 0;
}