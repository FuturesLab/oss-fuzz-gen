#include <cstddef>
#include <cstdint>
#include <cstring> // Include for std::memcpy
#include <tiffio.h>

extern "C" {
    // Include necessary C headers and functions
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a double
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize a double variable
    double value;

    // Copy bytes from the input data to the double variable
    std::memcpy(&value, data, sizeof(double));

    // Call the function-under-test
    TIFFSwabDouble(&value);

    return 0;
}