#include <cstdint>
#include <cmath>
#include <iostream>

// Assuming the function is defined elsewhere
extern "C" double LogL10toY(int x);

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer
    int x = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    double result = LogL10toY(x);

    // Optional: Print the result for debugging purposes
    std::cout << "LogL10toY(" << x << ") = " << result << std::endl;

    return 0;
}