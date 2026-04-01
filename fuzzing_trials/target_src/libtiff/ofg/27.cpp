#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form at least one double
    if (size < sizeof(double)) {
        return 0;
    }

    // Calculate the number of doubles we can form from the input data
    tmsize_t numDoubles = size / sizeof(double);

    // Allocate memory for the doubles
    double *doubleArray = static_cast<double*>(malloc(numDoubles * sizeof(double)));
    if (doubleArray == NULL) {
        return 0;
    }

    // Copy data into the double array
    for (tmsize_t i = 0; i < numDoubles; ++i) {
        doubleArray[i] = *reinterpret_cast<const double*>(data + i * sizeof(double));
    }

    // Call the function under test
    TIFFSwabArrayOfDouble(doubleArray, numDoubles);

    // Clean up
    free(doubleArray);

    return 0;
}