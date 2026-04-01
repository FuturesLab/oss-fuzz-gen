#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for the 'close' function

extern "C" {
    int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
        if (size < 1) {
            return 0;
        }

        // Create a temporary file to write the input data
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd == -1) {
            return 0;
        }

        FILE *file = fdopen(fd, "wb");
        if (!file) {
            close(fd);
            return 0;
        }

        fwrite(data, 1, size, file);
        fclose(file);

        // Open the temporary file as a TIFF
        TIFF *tiff = TIFFOpen(tmpl, "r");
        if (tiff == nullptr) {
            remove(tmpl);
            return 0;
        }

        // Create a non-null character array
        char msg[256] = "Test Message";

        // Call the function-under-test
        TIFFRGBAImageOK(tiff, msg);

        // Clean up
        TIFFClose(tiff);
        remove(tmpl);

        return 0;
    }
}