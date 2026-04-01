#include <cstdint>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for meaningful processing
    if (size == 0) {
        return 0;
    }

    // Create a temporary TIFF structure using TIFFClientOpen
    TIFF *tiff = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                                [](thandle_t, tdata_t, tmsize_t) -> tmsize_t { return 0; }, // Read function
                                [](thandle_t, tdata_t, tmsize_t) -> tmsize_t { return 0; }, // Write function
                                [](thandle_t, toff_t, int) -> toff_t { return 0; },        // Seek function
                                [](thandle_t) -> int { return 0; },                        // Close function
                                [](thandle_t) -> toff_t { return 0; },                     // Size function
                                [](thandle_t, void**, toff_t*) -> int { return 0; },       // Map function
                                [](thandle_t, tdata_t, toff_t) -> void {});                // Unmap function

    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    tmsize_t tileSize = TIFFTileSize(tiff);

    // Clean up
    TIFFClose(tiff);

    return 0;
}