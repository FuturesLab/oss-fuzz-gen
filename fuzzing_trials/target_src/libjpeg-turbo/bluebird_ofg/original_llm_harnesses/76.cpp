#include <cstdint>
#include <cstdlib>

// Assuming the function-under-test is part of a C library
extern "C" {
    int tjPlaneWidth(int componentID, int width, int subsampling);
}

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0]);
    int width = static_cast<int>(data[1]);
    int subsampling = static_cast<int>(data[2]);

    // Call the function-under-test with the extracted integers
    int result = tjPlaneWidth(componentID, width, subsampling);

    // Use the result in some way, here we just suppress unused variable warning
    (void)result;

    return 0;
}