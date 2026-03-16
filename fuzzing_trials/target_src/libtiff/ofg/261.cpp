#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a temporary TIFF file
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Use a non-null thandle_t value
    thandle_t clientdata = reinterpret_cast<thandle_t>(0x12345678);

    // Call the function-under-test
    TIFFSetClientdata(tiff, clientdata);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}