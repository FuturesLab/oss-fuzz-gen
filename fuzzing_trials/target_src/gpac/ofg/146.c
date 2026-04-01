#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Assuming the function returns an integer and takes a uint32_t as a parameter
int gf_isom_get_supported_box_type(uint32_t idx);

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an index
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract the index from the input data
    uint32_t idx;
    memcpy(&idx, data, sizeof(uint32_t));

    // Ensure the index is within a valid range if applicable
    // Assuming there is a maximum index value, e.g., MAX_INDEX
    // Define MAX_INDEX based on the expected range of idx
    const uint32_t MAX_INDEX = 1000; // Example value, adjust as needed
    if (idx > MAX_INDEX) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_supported_box_type(idx);

    return 0;
}