#include <cstdint>
#include <cstddef>
#include <cstring>

// Assuming OBU_TYPE is an enum defined in the library
enum OBU_TYPE {
    OBU_UNDEFINED = 0,
    OBU_SEQUENCE_HEADER,
    OBU_TEMPORAL_DELIMITER,
    OBU_FRAME,
    OBU_METADATA,
    // Add other OBU_TYPE values as necessary
};

extern "C" {
    const char * aom_obu_type_to_string(OBU_TYPE type);
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure that size is within the bounds of the OBU_TYPE enum
    if (size < sizeof(OBU_TYPE)) {
        return 0; // Not enough data to form a valid OBU_TYPE
    }

    // Initialize an OBU_TYPE variable
    OBU_TYPE type = static_cast<OBU_TYPE>(data[0] % (OBU_UNDEFINED + 5)); // Assuming 5 types for example

    // Call the function under test
    const char *result = aom_obu_type_to_string(type);

    // Optionally, you can use the result in some way
    // For example, you could print it, log it, or check for certain properties
    // However, for fuzzing purposes, we just call the function

    return 0;
}