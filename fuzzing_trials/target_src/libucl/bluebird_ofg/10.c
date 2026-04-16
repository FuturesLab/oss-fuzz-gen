#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
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

    LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
