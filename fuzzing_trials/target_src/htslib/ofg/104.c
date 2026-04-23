#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

// Assuming the function hts_readlist is declared in an external library
extern char ** hts_readlist(const char *filename, int is_file, int *n);

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the fuzzing data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create a temporary file
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // Error writing to the file
    }
    close(fd);

    // Prepare parameters for hts_readlist
    const char *filename = tmpl;
    int is_file = 1; // Indicate that the input is a file
    int n = 0;

    // Call the function-under-test
    char **result = hts_readlist(filename, is_file, &n);

    // Clean up
    if (result != NULL) {
        for (int i = 0; i < n; ++i) {
            free(result[i]);
        }
        free(result);
    }
    unlink(tmpl); // Remove the temporary file

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

    LLVMFuzzerTestOneInput_104(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
