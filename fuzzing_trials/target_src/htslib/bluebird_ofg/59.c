#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> // Include fcntl.h for file control options
#include "/src/htslib/ref_cache/types.h" // Include sys/types.h for system data types
#include <sys/stat.h> // Include sys/stat.h for file status

extern int sam_index_build(const char *filename, int option);

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // If there's no data, exit early
    }

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        perror("mkstemp failed");
        return 0; // If the file cannot be created, exit
    }

    // Ensure the file is truncated before writing
    if (ftruncate(fd, 0) != 0) {
        perror("ftruncate failed");
        close(fd);
        unlink(tmpl);
        return 0; // If truncation fails, clean up and exit
    }

    // Validate and sanitize the input data before writing
    // For demonstration, let's assume sam_index_build expects a specific header
    const char expected_header[] = "EXPECTED_HEADER";
    if (size < sizeof(expected_header) || memcmp(data, expected_header, sizeof(expected_header) - 1) != 0) {
        fprintf(stderr, "Invalid input format\n");
        close(fd);
        unlink(tmpl);
        return 0; // If the data doesn't match the expected format, exit
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        perror("write failed");
        close(fd);
        unlink(tmpl);
        return 0; // If the write fails, clean up and exit
    }
    
    close(fd); // Close the file descriptor

    // Call the function-under-test with the temporary file and a non-zero option
    int result = sam_index_build(tmpl, 1);

    // Optionally, handle the result of sam_index_build if needed
    if (result != 0) {
        // Handle error if sam_index_build fails
        fprintf(stderr, "sam_index_build failed with error code: %d\n", result);
    }

    // Clean up the temporary file
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

    LLVMFuzzerTestOneInput_59(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
