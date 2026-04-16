#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For mkstemp, write, lseek, close, and unlink
#include <fcntl.h>  // For file control options
#include <string.h> // For memset
#include "/src/htslib/htslib/hfile.h" // Correct path for hFILE

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Check if size is greater than zero to ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzer
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0; // If writing fails, exit the fuzzer
    }
    lseek(fd, 0, SEEK_SET); // Reset file pointer to the beginning
    close(fd); // Close the file descriptor since hopen will open it again

    // Open the file using hFILE
    hFILE *file = hopen(tmpl, "r");
    if (file == NULL) {
        unlink(tmpl); // Remove the temporary file
        return 0; // If hFILE opening fails, exit the fuzzer
    }

    // Allocate a buffer to read data into
    size_t buffer_size = 1024; // Arbitrary buffer size
    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        hclose(file);
        unlink(tmpl); // Remove the temporary file
        return 0; // If buffer allocation fails, exit the fuzzer
    }

    // Use a more comprehensive function to process the file
    ssize_t bytes_read;
    while ((bytes_read = hread(file, buffer, buffer_size)) > 0) {
        // Process the data read if needed
    }

    // Check for read errors
    if (bytes_read < 0) {
        // Handle error in hread if needed
    }

    // Clean up
    free(buffer);
    hclose(file);
    unlink(tmpl); // Remove the temporary file

    return 0;
}