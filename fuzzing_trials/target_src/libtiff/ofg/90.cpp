#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this header for the 'close' function

extern "C" {
    // Wrap libtiff functions and C standard library functions in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    
    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file with libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFDeferStrileArrayWriting(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}