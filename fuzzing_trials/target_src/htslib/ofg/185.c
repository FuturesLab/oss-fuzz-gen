#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include for mkstemp, close, unlink
#include <fcntl.h>   // Include for write
#include <string.h>  // Include for memcpy
#include "/src/htslib/htslib/hfile.h"  // Correct path for hfile.h

// Hypothetical function under test; replace with actual function
int process_data(const uint8_t *data, size_t size) {
    // Perform some operations on the data to increase code coverage
    if (size > 0) {
        // Example: Check for a specific pattern in the data
        if (size >= 4 && data[0] == 'F' && data[1] == 'U' && data[2] == 'Z' && data[3] == 'Z') {
            printf("Pattern 'FUZZ' found!\n");
            return 1;
        }
        // Example: Sum up all the bytes in the data
        int sum = 0;
        for (size_t i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum;
    }
    return 0;
}

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;  // Exit early if there's no data to process
    }

    // Create a temporary file to use with hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;  // If we can't create a temp file, exit early
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) == -1) {
        close(fd);
        unlink(tmpl);
        return 0;  // If writing fails, clean up and exit early
    }

    // Open the file using hFILE
    hFILE *hfile = hopen(tmpl, "r+");
    if (hfile == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;  // If opening fails, clean up and exit early
    }

    // Read the data back from the file
    uint8_t *buffer = malloc(size);
    if (buffer == NULL) {
        hclose(hfile);
        close(fd);
        unlink(tmpl);
        return 0;  // If memory allocation fails, clean up and exit early
    }

    if (hread(hfile, buffer, size) != size) {
        free(buffer);
        hclose(hfile);
        close(fd);
        unlink(tmpl);
        return 0;  // If reading fails, clean up and exit early
    }

    // Call the function-under-test with the read data
    int result = process_data(buffer, size);

    // Clean up
    free(buffer);
    hclose(hfile);
    close(fd);
    unlink(tmpl);

    return result;
}