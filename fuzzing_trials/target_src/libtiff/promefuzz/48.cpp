// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFFdOpen at tif_unix.c:209:7 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
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
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

static TIFF* openDummyFile(const char* mode) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        return nullptr;
    }
    return TIFFFdOpen(fd, "./dummy_file", mode);
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy file for testing
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file using TIFFFdOpen
    TIFF* tif = openDummyFile("r+");
    if (!tif) return 0;

    // Test TIFFSetSubDirectory
    if (Size >= sizeof(uint64_t)) {
        uint64_t subdirOffset;
        memcpy(&subdirOffset, Data, sizeof(uint64_t));
        TIFFSetSubDirectory(tif, subdirOffset);
    }

    // Test TIFFWriteCheck
    TIFFWriteCheck(tif, 1, "test");

    // Test TIFFReadDirectory
    TIFFReadDirectory(tif);

    // Test TIFFIsBigTIFF
    TIFFIsBigTIFF(tif);

    // Test TIFFReadScanline
    uint32_t row = 0;
    uint16_t sample = 0;
    void* buf = malloc(TIFFScanlineSize(tif));
    if (buf) {
        TIFFReadScanline(tif, buf, row, sample);
        free(buf);
    }

    // Cleanup
    TIFFClose(tif);
    unlink("./dummy_file");

    return 0;
}