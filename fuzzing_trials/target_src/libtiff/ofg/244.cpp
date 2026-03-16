#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Create a TIFF memory stream
    TIFF* tiff = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                                [](thandle_t fd, tdata_t buf, tsize_t size) -> tsize_t { return size; },
                                [](thandle_t fd, tdata_t buf, tsize_t size) -> tsize_t { return 0; },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t { return 0; },
                                [](thandle_t fd) -> int { return 0; },
                                [](thandle_t fd) -> toff_t { return 0; },
                                [](thandle_t fd, tdata_t* pbase, toff_t* psize) -> int { return 0; },
                                [](thandle_t fd, tdata_t base, toff_t size) -> void {});

    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFCreateGPSDirectory(tiff);

    // Close the TIFF memory stream
    TIFFClose(tiff);

    return 0;
}