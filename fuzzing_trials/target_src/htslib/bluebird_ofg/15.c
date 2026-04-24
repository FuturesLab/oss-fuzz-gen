#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> // Include for close() and unlink()
#include <fcntl.h>  // Include for mkstemp()

// Assuming the function is declared in some header file
char ** hts_readlist(const char *filename, int is_file, int *num_lines);

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzer
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Prepare parameters for hts_readlist
    int num_lines = 0;
    int is_file = 1; // Indicating that the input is a file

    // Call the function-under-test
    char **result = hts_readlist(tmpl, is_file, &num_lines);

    // Clean up: free the result if it is not NULL
    if (result != NULL) {
        for (int i = 0; i < num_lines; ++i) {
            free(result[i]);
        }
        free(result);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_15(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
