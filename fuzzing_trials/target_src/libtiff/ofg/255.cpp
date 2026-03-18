#include <cstdint>
#include <cstddef>

// Assuming the function is defined elsewhere
extern "C" double LogL16toY(int);

extern "C" int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer
    int input = static_cast<int>(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

    // Call the function-under-test
    double result = LogL16toY(input);

    // Use the result in some way (e.g., print, log, or further process)
    // For the purpose of this harness, we just call the function
    (void)result; // Suppress unused variable warning

    return 0;
}