#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least one byte for meaningful operations

    // Testing _TIFFmalloc and _TIFFmemset
    tmsize_t alloc_size = static_cast<tmsize_t>(Data[0]);
    void *memory = _TIFFmalloc(alloc_size);
    if (memory) {
        _TIFFmemset(memory, 0, alloc_size);
        _TIFFfree(memory);
    }

    // Testing _TIFFcalloc
    tmsize_t nmemb = static_cast<tmsize_t>(Data[0]);
    tmsize_t siz = alloc_size;
    void *calloc_memory = _TIFFcalloc(nmemb, siz);
    if (calloc_memory) {
        _TIFFfree(calloc_memory);
    }

    // Testing _TIFFmemcpy
    if (Size >= 2) {
        tmsize_t copy_size = static_cast<tmsize_t>(Data[1]);
        void *src = _TIFFmalloc(copy_size);
        void *dst = _TIFFmalloc(copy_size);
        if (src && dst) {
            _TIFFmemcpy(dst, src, copy_size);
        }
        _TIFFfree(src);
        _TIFFfree(dst);
    }

    // Testing _TIFFrealloc
    if (Size >= 3) {
        tmsize_t realloc_size = static_cast<tmsize_t>(Data[2]);
        void *realloc_memory = _TIFFmalloc(alloc_size);
        if (realloc_memory) {
            void *new_memory = _TIFFrealloc(realloc_memory, realloc_size);
            if (new_memory) {
                _TIFFfree(new_memory);
            } else {
                // Only free if realloc failed and did not return a new pointer
                // realloc_memory is not freed here because realloc already took care of it
            }
        }
    }

    // Testing TIFFWriteScanline
    if (Size >= 4) {
        TIFF *tif = TIFFOpen("./dummy_file", "w");
        if (tif) {
            void *buf = _TIFFmalloc(alloc_size);
            if (buf) {
                uint32_t row = static_cast<uint32_t>(Data[3]);
                uint16_t sample = 0; // Use a default sample value
                TIFFWriteScanline(tif, buf, row, sample);
                _TIFFfree(buf);
            }
            TIFFClose(tif);
        }
    }

    return 0;
}