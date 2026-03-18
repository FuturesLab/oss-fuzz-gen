#include <cstdint>
#include <cstddef>
#include <cstdio>

// Assuming the OBU_TYPE is an enum, define it here for the purpose of fuzzing.
extern "C" {
    typedef enum {
        OBU_SEQUENCE_HEADER = 0,
        OBU_TEMPORAL_DELIMITER = 1,
        OBU_FRAME_HEADER = 2,
        OBU_TILE_GROUP = 3,
        OBU_METADATA = 4,
        OBU_FRAME = 5,
        OBU_REDUNDANT_FRAME_HEADER = 6,
        OBU_TILE_LIST = 7,
        OBU_PADDING = 15,
        OBU_INVALID = 16  // Assuming an invalid type for fuzzing purposes
    } OBU_TYPE;

    // Declaration of the function-under-test
    const char * aom_obu_type_to_string(OBU_TYPE type);
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure that there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the OBU_TYPE
    OBU_TYPE type = static_cast<OBU_TYPE>(data[0] % 17);  // Modulo with 17 to cover all defined types including OBU_INVALID

    // Call the function-under-test
    const char *result = aom_obu_type_to_string(type);

    // Optionally, print the result for debugging purposes
    if (result != nullptr) {
        printf("OBU Type: %d, String: %s\n", type, result);
    }

    return 0;
}