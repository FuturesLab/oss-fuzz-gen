#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" {
    void TIFFSwabLong8(uint64_t *);
}

extern "C" int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0; // Ensure there is enough data to form a uint64_t
    }

    uint64_t value;
    // Copy the first 8 bytes of data into value, assuming little-endian architecture
    value = static_cast<uint64_t>(data[0]) |
            (static_cast<uint64_t>(data[1]) << 8) |
            (static_cast<uint64_t>(data[2]) << 16) |
            (static_cast<uint64_t>(data[3]) << 24) |
            (static_cast<uint64_t>(data[4]) << 32) |
            (static_cast<uint64_t>(data[5]) << 40) |
            (static_cast<uint64_t>(data[6]) << 48) |
            (static_cast<uint64_t>(data[7]) << 56);

    // Call the function-under-test
    TIFFSwabLong8(&value);

    return 0;
}