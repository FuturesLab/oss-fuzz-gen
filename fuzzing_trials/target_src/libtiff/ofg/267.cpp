#include <cstdint>
#include <cstdio>
#include <unistd.h>   // For close, write, and mkstemp
#include <sys/types.h> // For ssize_t
#include <cstdlib>    // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint64_t diroff = 0;

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file with TIFF library
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Use the first 8 bytes of data as the directory offset
    if (size >= sizeof(uint64_t)) {
        diroff = *reinterpret_cast<const uint64_t*>(data);
    }

    // Call the function-under-test
    TIFFSetSubDirectory(tiff, diroff);

    // Cleanup
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}