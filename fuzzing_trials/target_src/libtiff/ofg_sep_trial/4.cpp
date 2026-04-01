#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(float)) {
        return 0;
    }

    // Calculate the number of floats we can create from the input data
    tmsize_t numFloats = size / sizeof(float);

    // Allocate memory for the float array
    float *floatArray = static_cast<float *>(malloc(numFloats * sizeof(float)));
    if (floatArray == nullptr) {
        return 0;
    }

    // Copy data into the float array
    for (tmsize_t i = 0; i < numFloats; ++i) {
        floatArray[i] = reinterpret_cast<const float *>(data)[i];
    }

    // Call the function-under-test
    TIFFSwabArrayOfFloat(floatArray, numFloats);

    // Clean up
    free(floatArray);

    return 0;
}