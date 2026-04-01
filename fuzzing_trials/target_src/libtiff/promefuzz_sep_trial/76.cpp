// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetMaxCumulatedMemAlloc at tif_open.c:106:6 in tiffio.h
// TIFFFdOpen at tif_unix.c:209:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFFdOpenExt at tif_unix.c:214:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
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
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy file for testing
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file descriptor
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return 0;

    // Allocate TIFFOpenOptions
    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (!opts) {
        close(fd);
        return 0;
    }

    // Set a random memory allocation limit
    tmsize_t maxMemAlloc = static_cast<tmsize_t>(Data[0]);
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(opts, maxMemAlloc);

    // Try opening the TIFF file with various functions
    TIFF *tiff = nullptr;
    
    // Using TIFFFdOpen
    tiff = TIFFFdOpen(fd, filename, "r");
    if (tiff) TIFFClose(tiff);

    // Using TIFFFdOpenExt
    tiff = TIFFFdOpenExt(fd, filename, "r", opts);
    if (tiff) TIFFClose(tiff);

    // Using TIFFOpenExt
    tiff = TIFFOpenExt(filename, "r", opts);
    if (tiff) TIFFClose(tiff);

    // Clean up
    TIFFClose(tiff);
    TIFFOpenOptionsFree(opts);
    close(fd);
    unlink(filename);

    return 0;
}