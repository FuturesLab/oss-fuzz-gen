#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close() and write()
#include <sys/types.h> // Include for ssize_t
#include <sys/stat.h>
#include <fcntl.h> // Include for mkstemp()

extern "C" int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
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

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        return 0;
    }

    // Define some non-NULL values for tag and datatype
    uint32_t tag = 0; // Example tag, modify as needed
    TIFFDataType datatype = TIFFDataType::TIFF_NOTYPE; // Example datatype, modify as needed

    // Call the function-under-test
    const TIFFField *field = TIFFFindField(tiff, tag, datatype);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}