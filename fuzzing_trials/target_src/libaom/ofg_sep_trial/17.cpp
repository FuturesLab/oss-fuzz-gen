#include <cstdint>
#include <cstddef>
#include <cstdio>

extern "C" {
    // Include the necessary header for the function-under-test
    #include "aom/aom_codec.h"  // Assuming this is where OBU_TYPE is defined
}

// Fuzzing harness for the function-under-test
extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract an OBU_TYPE
    if (size < sizeof(OBU_TYPE)) {
        return 0;
    }

    // Extract an OBU_TYPE from the input data
    OBU_TYPE obu_type = static_cast<OBU_TYPE>(data[0] % 5); // Assuming there are 5 OBU_TYPEs

    // Call the function-under-test
    const char *result = aom_obu_type_to_string(obu_type);

    // Print the result for debugging purposes
    if (result != nullptr) {
        printf("OBU_TYPE: %d, String: %s\n", obu_type, result);
    }

    return 0;
}