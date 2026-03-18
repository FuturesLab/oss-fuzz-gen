#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // For POSIX functions: write, close, remove
#include <fcntl.h>   // For mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file using libtiff
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (tif == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFRewriteDirectory(tif);

    // Close the TIFF file and remove the temporary file
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}