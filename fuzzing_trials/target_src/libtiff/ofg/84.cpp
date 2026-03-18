#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the library for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Create a memory stream from the input data
    if (size == 0) {
        return 0;
    }

    // Open a TIFF file from the memory buffer
    TIFF* tiff = TIFFClientOpen("MemTIFF", "r", (thandle_t)data,
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t {
                                    memcpy(buf, (void*)fd, size);
                                    return size;
                                },
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t {
                                    return 0;
                                },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t {
                                    return (toff_t)off;
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
                                    // Unmap function, no operation needed
                                });

    if (tiff == nullptr) {
        return 0;
    }

    // Call the function under test
    tmsize_t scanlineSize = TIFFScanlineSize(tiff);

    // Use the result to avoid compiler optimizations
    if (scanlineSize == 0) {
        TIFFClose(tiff);
        return 0;
    }

    TIFFClose(tiff);
    return 0;
}