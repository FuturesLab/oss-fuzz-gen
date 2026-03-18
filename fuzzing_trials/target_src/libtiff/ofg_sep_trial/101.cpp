#include <cstdint>
#include <cstring>
#include <cstdio>
#include <unistd.h>  // For mkstemp, write, close
#include <sys/types.h>  // For ssize_t
#include <cstdlib>  // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
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

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Ensure the name is null-terminated and not NULL
    char fieldName[256] = "SampleFieldName";
    if (size > 0) {
        size_t copySize = size < sizeof(fieldName) ? size : sizeof(fieldName) - 1;
        std::memcpy(fieldName, data, copySize);
        fieldName[copySize] = '\0'; // Ensure null-termination
    }

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithName(tiff, fieldName);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}