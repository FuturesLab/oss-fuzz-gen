#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close and write functions

extern "C" int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    TIFF* tiff = nullptr;
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

    // Close the file descriptor so TIFF can open it
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFSeekProc seekProc = TIFFGetSeekProc(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}