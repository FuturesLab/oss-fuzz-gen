#include "cstdint"
#include "cstdlib"
#include "cstring" // Include the header for memcpy
#include "tiffio.h"

extern "C" {
    // Include necessary C headers and function declarations here.
    void TIFFSwabArrayOfDouble(double *, tmsize_t);
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of the size of double to avoid out-of-bounds access
    if (size < sizeof(double) || size % sizeof(double) != 0) {
        return 0;
    }

    // Calculate the number of doubles
    tmsize_t numDoubles = static_cast<tmsize_t>(size / sizeof(double));

    // Allocate memory for the double array
    double* doubleArray = static_cast<double*>(malloc(size));
    if (doubleArray == nullptr) {
        return 0;
    }

    // Copy the input data into the double array
    memcpy(doubleArray, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfDouble(doubleArray, numDoubles);

    // Free the allocated memory
    free(doubleArray);

    return 0;
}