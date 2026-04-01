#include <cstdint>
#include <cstddef>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Since TIFF is an opaque structure, we cannot use sizeof(TIFF).
    // Instead, we just ensure there's some data to work with.
    if (size == 0) {
        return 0;
    }

    // Create a TIFF object from the input data
    TIFF *tiff = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                                [](thandle_t fd, tdata_t buf, tsize_t size) -> tsize_t { return size; },
                                [](thandle_t fd, tdata_t buf, tsize_t size) -> tsize_t { return size; },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t { return off; },
                                [](thandle_t fd) -> int { return 0; },
                                [](thandle_t fd) -> toff_t { return 0; },
                                [](thandle_t fd, tdata_t* pbase, toff_t* psize) -> int { return 0; },
                                [](thandle_t fd, tdata_t base, toff_t size) -> void {});

    if (tiff != nullptr) {
        // Call the function under test
        uint64_t scanlineSize = TIFFScanlineSize64(tiff);

        // Clean up
        TIFFClose(tiff);
    }

    return 0;
}