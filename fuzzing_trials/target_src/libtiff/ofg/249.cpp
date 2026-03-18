#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cstring> // Include for memcpy

// Function under test
extern "C" int LogL16fromY(double y, int x);

extern "C" int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    if (size < sizeof(double) + sizeof(int)) {
        return 0; // Not enough data to form valid inputs
    }

    // Extract a double and an int from the input data
    double y;
    int x;

    // Copy the data into the variables
    memcpy(&y, data, sizeof(double));
    memcpy(&x, data + sizeof(double), sizeof(int));

    // Call the function under test
    LogL16fromY(y, x);

    return 0;
}