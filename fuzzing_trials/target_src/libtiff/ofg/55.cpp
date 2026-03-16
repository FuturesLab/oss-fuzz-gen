#include <cstdint>
#include <cstdio>
#include <unistd.h>  // Include for close, write, and mkstemp
#include <cstdlib>   // Include for remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint32_t tile = TIFFCurrentTile(tif);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}