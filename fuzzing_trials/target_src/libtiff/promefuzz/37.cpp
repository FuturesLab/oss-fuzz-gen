// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemset at tif_unix.c:353:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFcalloc at tif_unix.c:341:7 in tiffio.h
// _TIFFmemset at tif_unix.c:353:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFrealloc at tif_unix.c:351:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemset at tif_unix.c:353:6 in tiffio.h
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
#include <cstdio>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz _TIFFmalloc
    tmsize_t malloc_size = static_cast<tmsize_t>(Data[0]);
    void *malloc_ptr = _TIFFmalloc(malloc_size);
    if (malloc_ptr) {
        _TIFFmemset(malloc_ptr, 0, malloc_size);
        _TIFFfree(malloc_ptr);
    }

    // Fuzz _TIFFcalloc
    if (Size >= 2) {
        tmsize_t nmemb = static_cast<tmsize_t>(Data[1]);
        tmsize_t siz = static_cast<tmsize_t>(Data[0]);
        void *calloc_ptr = _TIFFcalloc(nmemb, siz);
        if (calloc_ptr) {
            _TIFFmemset(calloc_ptr, 0, nmemb * siz);
            _TIFFfree(calloc_ptr);
        }
    }

    // Fuzz _TIFFrealloc
    if (Size >= 3) {
        tmsize_t realloc_size = static_cast<tmsize_t>(Data[2]);
        void *realloc_ptr = _TIFFmalloc(malloc_size);
        if (realloc_ptr) {
            void *new_realloc_ptr = _TIFFrealloc(realloc_ptr, realloc_size);
            if (new_realloc_ptr != nullptr) {
                _TIFFfree(new_realloc_ptr);
            }
        }
    }

    // Fuzz TIFFWriteScanline
    TIFF* tif = TIFFOpen("./dummy_file", "w");
    if (tif) {
        void *buf = _TIFFmalloc(Size);
        if (buf) {
            _TIFFmemcpy(buf, Data, Size);
            TIFFWriteScanline(tif, buf, 0, 0);
            _TIFFfree(buf);
        }
        TIFFClose(tif);
    }

    // Fuzz _TIFFmemcpy
    if (Size >= 4) {
        tmsize_t copy_size = static_cast<tmsize_t>(Data[3]);
        if (copy_size > 0 && copy_size <= Size) {
            void *dest = _TIFFmalloc(copy_size);
            if (dest) {
                _TIFFmemcpy(dest, Data, copy_size);
                _TIFFfree(dest);
            }
        }
    }

    // Fuzz _TIFFmemset
    if (Size >= 5) {
        tmsize_t memset_size = static_cast<tmsize_t>(Data[4]);
        if (memset_size > 0) {
            void *memset_ptr = _TIFFmalloc(memset_size);
            if (memset_ptr) {
                _TIFFmemset(memset_ptr, Data[0], memset_size);
                _TIFFfree(memset_ptr);
            }
        }
    }

    return 0;
}