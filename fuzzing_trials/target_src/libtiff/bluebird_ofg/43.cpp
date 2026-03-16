#include "cstdint"
#include <cstdio>

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a TIFF structure.
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a TIFF structure.
    TIFF *tiff = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                                [](thandle_t, void* buf, tmsize_t size) -> tmsize_t { return size; }, // Read function
                                [](thandle_t, void*, tmsize_t) -> tmsize_t { return 0; }, // Write function
                                [](thandle_t, uint64_t, int) -> uint64_t { return 0; }, // Seek function
                                [](thandle_t) -> int { return 0; },               // Close function
                                [](thandle_t) -> toff_t { return 0; },               // Size function
                                nullptr, nullptr);

    if (!tiff) {
        return 0;
    }

    // Use the first 4 bytes of data as the uint32_t parameter for TIFFVStripSize64
    uint32_t stripIndex = *reinterpret_cast<const uint32_t*>(data);

    // Call the function-under-test
    uint64_t stripSize = TIFFVStripSize64(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);

    return 0;
}