// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemset at tif_unix.c:353:6 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// _TIFFmemcmp at tif_unix.c:360:5 in tiffio.h
// _TIFFrealloc at tif_unix.c:351:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least 1 byte for meaningful operations

    // Test _TIFFmalloc
    tmsize_t alloc_size = static_cast<tmsize_t>(Data[0]);
    void *memory = _TIFFmalloc(alloc_size);
    if (!memory) return 0; // Allocation failed, exit early

    // Test _TIFFmemset
    int set_value = Data[0];
    _TIFFmemset(memory, set_value, alloc_size);

    // Test _TIFFmemcpy
    if (Size > 1) {
        tmsize_t copy_size = (Size - 1) < alloc_size ? (Size - 1) : alloc_size;
        _TIFFmemcpy(memory, Data + 1, copy_size);
    }

    // Test _TIFFmemcmp
    if (Size > 2) {
        int cmp_result = _TIFFmemcmp(memory, Data + 2, alloc_size > (Size - 2) ? (Size - 2) : alloc_size);
        (void)cmp_result; // Suppress unused variable warning
    }

    // Test _TIFFrealloc
    if (Size > 3) {
        tmsize_t realloc_size = static_cast<tmsize_t>(Data[3]);
        void *reallocated_memory = _TIFFrealloc(memory, realloc_size);
        if (reallocated_memory) {
            memory = reallocated_memory;
        } else {
            // If realloc fails, the original memory block is not freed
            // so we should not attempt to free it here
            return 0;
        }
    }

    // Cleanup
    if (memory) {
        _TIFFfree(memory);
    }

    return 0;
}