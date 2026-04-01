#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure there's enough data to form at least one double
    if (size < sizeof(double)) {
        return 0;
    }

    // Calculate the number of doubles we can extract from the input data
    tmsize_t numDoubles = size / sizeof(double);

    // Allocate memory for the double array
    double *doubleArray = static_cast<double *>(malloc(numDoubles * sizeof(double)));
    if (doubleArray == nullptr) {
        return 0; // Memory allocation failed
    }

    // Copy data into the double array
    for (tmsize_t i = 0; i < numDoubles; ++i) {
        doubleArray[i] = reinterpret_cast<const double *>(data)[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfDouble(doubleArray, numDoubles);

    // Clean up
    free(doubleArray);

    return 0;
}