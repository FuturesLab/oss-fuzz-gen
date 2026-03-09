#include <cstdint>
#include <cstddef>
#include <cstdio>

extern "C" {
    #include "aom/aom_codec.h"
    #include "aom/aomcx.h"
    #include "aom/aom_decoder.h"
    #include "aom/aom_encoder.h"
    // Removed #include "aom/obu.h" as it does not exist
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Interpret the first byte of data as an OBU_TYPE
    OBU_TYPE obu_type = static_cast<OBU_TYPE>(data[0] % 16); // Assuming OBU_TYPE is an enum with values 0-15

    // Call the function-under-test
    const char *result = aom_obu_type_to_string(obu_type);

    // Print the result for debugging purposes
    if (result != nullptr) {
        printf("OBU_TYPE: %d, String: %s\n", obu_type, result);
    } else {
        printf("OBU_TYPE: %d, String: NULL\n", obu_type);
    }

    return 0;
}