extern "C" {
#include <tiffio.h>
#include <unistd.h>
#include <fcntl.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file using the temporary file path
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    const char* filename = TIFFFileName(tiff);

    // Print the filename for debugging purposes
    if (filename != nullptr) {
        printf("TIFF File Name: %s\n", filename);
    }

    // Close the TIFF file
    TIFFClose(tiff);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}