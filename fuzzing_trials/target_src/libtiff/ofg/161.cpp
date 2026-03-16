#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy
#include <unistd.h> // Include for write, close, unlink
#include <fcntl.h> // Include for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Instead of using sizeof(TIFF), use a realistic size for the data buffer
    // as we cannot know the size of the TIFF struct from the header.
    // Let's assume a minimum size for a valid TIFF header or data block.
    const size_t min_tiff_data_size = 8; // Example size, adjust as necessary

    if (size < min_tiff_data_size) {
        return 0;
    }

    // Create a temporary file to simulate the TIFF file from memory
    char tmp_filename[] = "/tmp/tiff_fuzz_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        unlink(tmp_filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF
    TIFF* tiff = TIFFOpen(tmp_filename, "r");
    if (tiff == NULL) {
        unlink(tmp_filename);
        return 0;
    }

    // Call the function-under-test
    TIFFFreeDirectory(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Clean up the temporary file
    unlink(tmp_filename);

    return 0;
}