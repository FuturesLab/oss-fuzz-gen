#include <cstdint>
#include <cstddef>
#include <iostream>

// Assuming OBU_TYPE is an enum or a type that can be represented as an integer
typedef int OBU_TYPE;

// Function signature from the task
extern "C" const char * aom_obu_type_to_string(OBU_TYPE obu_type);

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure we have enough data to derive an OBU_TYPE
    if (size < sizeof(OBU_TYPE)) {
        return 0;
    }

    // Use the first bytes of data to create an OBU_TYPE
    OBU_TYPE obu_type = static_cast<OBU_TYPE>(data[0]);

    // Call the function under test
    const char *result = aom_obu_type_to_string(obu_type);

    // Optional: Print the result for debugging purposes
    if (result != nullptr) {
        std::cout << "OBU_TYPE: " << obu_type << " -> " << result << std::endl;
    } else {
        std::cout << "OBU_TYPE: " << obu_type << " -> NULL" << std::endl;
    }

    return 0;
}