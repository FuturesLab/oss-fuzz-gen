#include <cstdint>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstdio>  // Include this header for the remove function

// Include the necessary header for the function-under-test
extern "C" {
    int plist_is_binary(const char *filename, uint32_t options);
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a filename and provide meaningful content
    if (size < 4) {  // Assuming a minimum size for a valid plist
        return 0;
    }

    // Create a temporary filename using the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    ssize_t written = write(fd, data, size);
    close(fd);

    // Ensure data was written successfully
    if (written != size) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test with the temporary filename and a non-zero options value
    uint32_t options = 1;
    plist_is_binary(tmpl, options);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}