#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include this for 'close' and 'mkstemp'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Create a temporary file to work with TIFF operations
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Fuzzing the TIFFUnlinkDirectory function
    tdir_t dirnum = 0; // Initialize directory number to 0
    if (size > 0) {
        dirnum = static_cast<tdir_t>(data[0]); // Use the first byte of data as directory number
    }

    // Call the function-under-test
    TIFFUnlinkDirectory(tiff, dirnum);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}