// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFFdOpen at tif_unix.c:209:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include <tiffio.h>
#include <fcntl.h>
#include <unistd.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    // Open the dummy file and obtain a file descriptor
    int fd = open("./dummy_file", O_RDWR);
    if (fd == -1) {
        return 0;
    }

    // Attempt to open the TIFF file using the file descriptor
    TIFF *tif = TIFFFdOpen(fd, "dummy_file", "r+");
    if (!tif) {
        close(fd);
        return 0;
    }

    // Allocate a buffer for reading a scanline
    tmsize_t scanlineSize = TIFFScanlineSize(tif);
    void *buf = malloc(scanlineSize);
    if (!buf) {
        TIFFClose(tif);
        close(fd);
        return 0;
    }

    // Attempt to read the first scanline
    TIFFReadScanline(tif, buf, 0, 0);

    // Check if the TIFF is a BigTIFF
    TIFFIsBigTIFF(tif);

    // Attempt to read the directory
    TIFFReadDirectory(tif);

    // Attempt to set a subdirectory
    TIFFSetSubDirectory(tif, 0);

    // Check if the TIFF is ready for writing
    TIFFWriteCheck(tif, 1, "dummy_file");

    // Clean up
    free(buf);
    TIFFClose(tif);
    close(fd);

    return 0;
}