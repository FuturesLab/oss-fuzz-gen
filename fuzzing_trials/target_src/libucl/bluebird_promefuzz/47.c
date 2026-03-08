#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "stdio.h"
#include "unistd.h"
#include <fcntl.h>

static void test_ucl_parser_add_string(struct ucl_parser *parser, const uint8_t *data, size_t size) {
    if (parser) {
        // Ensure the data is null-terminated if size is 0
        char *null_terminated_data = (char *)malloc(size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, data, size);
            null_terminated_data[size] = '\0';

            // Try adding the string with the exact size
            ucl_parser_add_string(parser, null_terminated_data, size);

            // Try adding the string assuming it's null-terminated

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ucl_parser_add_string
            ucl_parser_add_string(parser, NULL, 0);
            // End mutation: Producer.REPLACE_ARG_MUTATOR



            free(null_terminated_data);
        }
    }
}

static void test_ucl_parser_add_fd(struct ucl_parser *parser, const uint8_t *data, size_t size) {
    if (parser) {
        int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd != -1) {
            write(fd, data, size);
            lseek(fd, 0, SEEK_SET);
            ucl_parser_add_fd(parser, fd);
            close(fd);
        }
    }
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);

    if (parser) {
        // Fuzz ucl_parser_add_string
        test_ucl_parser_add_string(parser, Data, Size);

        // Fuzz ucl_parser_add_fd
        test_ucl_parser_add_fd(parser, Data, Size);

        // Fuzz ucl_parser_get_default_priority
        int priority = ucl_parser_get_default_priority(parser);

        // Fuzz ucl_parser_get_error_code
        int error_code = ucl_parser_get_error_code(parser);

        // Fuzz ucl_parser_get_error
        const char *error_str = ucl_parser_get_error(parser);

        // Clean up
        ucl_parser_free(parser);
    }
    return 0;
}