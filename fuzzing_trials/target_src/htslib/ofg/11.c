#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for close() and mkstemp()

// Assuming hFILE is a structure defined elsewhere
typedef struct {
    FILE *file;
} hFILE;

// Mock implementation of hpeek_11 for demonstration purposes
ssize_t hpeek_11(hFILE *hfile, void *buffer, size_t size) {
    if (hfile == NULL || buffer == NULL || hfile->file == NULL) {
        return -1;
    }

    return fread(buffer, 1, size, hfile->file);
}

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure there is at least some data to work with
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to simulate hFILE's file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb+");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    rewind(file);

    // Initialize hFILE structure
    hFILE hfile;
    hfile.file = file;

    // Allocate a buffer to read data into
    size_t buffer_size = size > 1024 ? 1024 : size; // Limit buffer size for safety
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fclose(file);
        return 0;
    }

    // Call the function-under-test
    ssize_t bytes_read = hpeek_11(&hfile, buffer, buffer_size);

    // Check the result of hpeek_11 and ensure it reads data
    if (bytes_read > 0) {
        // Process the data read if necessary
        // For demonstration, just print the number of bytes read
        printf("Bytes read: %zd\n", bytes_read);
    }

    // Clean up
    free(buffer);
    fclose(file);
    remove(tmpl);

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

    LLVMFuzzerTestOneInput_11(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
