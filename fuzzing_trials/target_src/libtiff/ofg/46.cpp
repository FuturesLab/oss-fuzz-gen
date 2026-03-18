#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp
#include <unistd.h> // For close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary file to act as a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb+");
    if (file == nullptr) {
        close(fd);
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fflush(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        fclose(file);
        return 0;
    }

    // Use the first few bytes of data to set the file number
    int fileno = *reinterpret_cast<const int*>(data);

    // Call the function-under-test
    TIFFSetFileno(tiff, fileno);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}