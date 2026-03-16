#include "cstdint"
#include <cstddef>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of the size of float
    if (size % sizeof(float) != 0 || size == 0) {
        return 0;
    }

    // Calculate the number of float elements
    tmsize_t numFloats = size / sizeof(float);

    // Allocate memory for the float array
    float *floatArray = new float[numFloats];

    // Copy data into the float array
    for (tmsize_t i = 0; i < numFloats; ++i) {
        floatArray[i] = reinterpret_cast<const float*>(data)[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfFloat(floatArray, numFloats);

    // Clean up
    delete[] floatArray;

    return 0;
}