#include <cstdint>
#include <cstdio>
#include <unistd.h>  // For close, write, and mkstemp
#include <cstdlib>   // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint64_t dirOffset = TIFFCurrentDirOffset(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}