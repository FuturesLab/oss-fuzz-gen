#include <cstdint>
#include <cstddef>
#include <cstring>
#include <tiffio.h>

extern "C" {
    // Function prototype for the function-under-test
    void TIFFSwabShort(uint16_t *);
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Declare and initialize a uint16_t variable
    uint16_t value;
    memcpy(&value, data, sizeof(uint16_t));

    // Call the function-under-test
    TIFFSwabShort(&value);

    return 0;
}