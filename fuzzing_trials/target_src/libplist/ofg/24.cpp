#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib> // Include for mkstemp

extern "C" {
    // Include the header for the function-under-test
    int plist_is_binary(const char *, uint32_t);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Call the function-under-test with the temporary file name and a non-zero uint32_t value
    uint32_t some_value = 1; // Example non-zero value
    plist_is_binary(tmpl, some_value);

    // Clean up: remove the temporary file
    unlink(tmpl);

    return 0;
}