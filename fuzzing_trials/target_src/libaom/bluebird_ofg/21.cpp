#include <cstdint>
#include <cstddef>
#include <cstring>
#include "/src/aom/aom/aom_integer.h"  // Assuming this is where aom_uleb_encode is declared

extern "C" {
    // Include the function-under-test
    int aom_uleb_encode(uint64_t value, size_t available, uint8_t *coded, size_t *coded_size);
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize variables
    uint64_t value = 12345; // A non-zero arbitrary value
    size_t available = size > 0 ? size : 1; // Ensure available is at least 1
    uint8_t *coded = new uint8_t[available]; // Allocate memory for coded
    size_t coded_size = 0; // Initialize coded_size

    // Ensure data is not NULL and size is greater than 0
    if (data != nullptr && size > 0) {
        // Call the function-under-test
        aom_uleb_encode(value, available, coded, &coded_size);
    }

    // Clean up allocated memory
    delete[] coded;

    return 0;
}