#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>  // Include this for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    toff_t offset = 0;

    // Create a temporary file to initialize the TIFF structure
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Rewind the file descriptor
    lseek(fd, 0, SEEK_SET);

    // Open the TIFF file
    tiff = TIFFFdOpen(fd, tmpl, "r+");
    if (tiff == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Use the first 8 bytes of data as the offset, if available
    if (size >= sizeof(toff_t)) {
        offset = *reinterpret_cast<const toff_t*>(data);
    }

    // Call the function-under-test
    TIFFSetWriteOffset(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}