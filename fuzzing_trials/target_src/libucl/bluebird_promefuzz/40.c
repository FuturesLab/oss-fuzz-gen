#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
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
            ucl_parser_add_string(parser, null_terminated_data, 0);

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

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_error_code to ucl_parser_add_string
        double ret_ucl_object_todouble_csubv = ucl_object_todouble(NULL);
        if (ret_ucl_object_todouble_csubv < 0){
        	return 0;
        }
        bool ret_ucl_parser_add_string_xuupd = ucl_parser_add_string(parser, NULL, (size_t )ret_ucl_object_todouble_csubv);
        if (ret_ucl_parser_add_string_xuupd == 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        const char *error_str = ucl_parser_get_error(parser);

        // Clean up
        ucl_parser_free(parser);
    }

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_40(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
