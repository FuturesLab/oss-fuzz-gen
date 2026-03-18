#include <cstdint>
#include <cstdlib>

// Assuming the function is part of a C library, we wrap it with extern "C"
extern "C" {
    int tjPlaneWidth(int componentID, int width, int subsamp);
}

// Fuzzing harness for tjPlaneWidth
extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0]);
    int width = static_cast<int>(data[1]);
    int subsamp = static_cast<int>(data[2]);

    // Call the function-under-test
    int result = tjPlaneWidth(componentID, width, subsamp);

    // Use the result in some way to avoid compiler optimizations
    volatile int sink = result;
    (void)sink;

    return 0;
}