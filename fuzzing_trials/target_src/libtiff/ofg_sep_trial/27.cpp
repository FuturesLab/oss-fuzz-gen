#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of the size of double to avoid incomplete double values
    if (size % sizeof(double) != 0) {
        return 0;
    }

    // Calculate the number of double elements
    tmsize_t numDoubles = size / sizeof(double);

    // Allocate memory for an array of doubles
    double *doubleArray = static_cast<double *>(malloc(size));
    if (doubleArray == nullptr) {
        return 0;
    }

    // Copy the input data into the double array
    memcpy(doubleArray, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfDouble(doubleArray, numDoubles);

    // Free allocated memory
    free(doubleArray);

    return 0;
}