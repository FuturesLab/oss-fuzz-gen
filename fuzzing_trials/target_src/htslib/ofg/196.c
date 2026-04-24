#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include this for mkstemp, write, close, and unlink

// Assuming the function hts_readlines is declared in some header file
extern char **hts_readlines(const char *, int *);

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0; // If writing fails, clean up and exit early
    }

    close(fd); // Close the file descriptor

    // Prepare an integer to receive the number of lines read
    int num_lines = 0;

    // Call the function-under-test
    char **lines = hts_readlines(tmpl, &num_lines);

    // Clean up: free the lines array if it was allocated
    if (lines != NULL) {
        for (int i = 0; i < num_lines; ++i) {
            free(lines[i]);
        }
        free(lines);
    }

    // Remove the temporary file
    unlink(tmpl);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_196(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
