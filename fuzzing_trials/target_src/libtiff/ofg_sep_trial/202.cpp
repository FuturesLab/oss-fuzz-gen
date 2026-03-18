#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a dummy TIFF structure
    // Since we cannot determine the size of TIFF, we will not use sizeof(TIFF)
    // Instead, we will rely on the function that can handle a TIFF* pointer

    // Use TIFFClientOpen to read from the data buffer
    TIFF* memTiff = TIFFClientOpen("mem", "r", (thandle_t)data,
                                   [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t {
                                       memcpy(buf, (void*)fd, size);
                                       return size;
                                   },
                                   [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t {
                                       return 0;
                                   },
                                   [](thandle_t fd, toff_t off, int whence) -> toff_t {
                                       return 0;
                                   },
                                   [](thandle_t fd) -> int {
                                       return 0;
                                   },
                                   [](thandle_t fd) -> toff_t {
                                       return 0;
                                   },
                                   [](thandle_t fd, void** pbase, toff_t* psize) -> int {
                                       return 0;
                                   },
                                   [](thandle_t fd, void* base, toff_t size) -> void {
                                   });

    if (memTiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    tmsize_t rowSize = TIFFTileRowSize(memTiff);

    // Clean up
    TIFFClose(memTiff);

    return 0;
}