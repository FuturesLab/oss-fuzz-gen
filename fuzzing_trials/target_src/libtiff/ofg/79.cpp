#include <cstdint>
#include <cstddef>
#include <cstring>  // Include for std::memcpy
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure we have enough data to form a double
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize a double variable
    double value;

    // Copy the data into the double variable
    // This assumes the data is aligned and valid for a double
    std::memcpy(&value, data, sizeof(double));

    // Call the function-under-test
    TIFFSwabDouble(&value);

    return 0;
}