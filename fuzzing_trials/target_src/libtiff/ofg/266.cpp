#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tiffio.h>
#include <cstdlib> // Include this for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint64_t diroff = 0;

    if (size < sizeof(uint64_t)) {
        return 0; // Not enough data to form a valid directory offset
    }

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0; // Failed to write all data to the file
    }

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        close(fd);
        unlink(tmpl);
        return 0; // Failed to open the file as a TIFF
    }

    // Extract a 64-bit integer from the input data to use as the directory offset
    diroff = *reinterpret_cast<const uint64_t*>(data);

    // Call the function-under-test
    TIFFSetSubDirectory(tiff, diroff);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl); // Remove the temporary file

    return 0;
}