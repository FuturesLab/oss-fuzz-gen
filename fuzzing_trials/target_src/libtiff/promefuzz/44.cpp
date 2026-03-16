// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFFdOpen at tif_unix.c:209:7 in tiffio.h
// TIFFSetMode at tif_open.c:853:5 in tiffio.h
// TIFFReadBufferSetup at tif_read.c:1385:5 in tiffio.h
// TIFFFileno at tif_open.c:818:5 in tiffio.h
// TIFFFlush at tif_flush.c:30:5 in tiffio.h
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
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file descriptor
    int fd = open(filename, O_RDWR);
    if (fd < 0) return 0;

    // Attempt to open a TIFF file using the file descriptor
    TIFF *tif = TIFFFdOpen(fd, filename, "r+");
    if (!tif) {
        close(fd);
        return 0;
    }

    // Fuzz TIFFSetMode
    int mode = Data[0] % 3; // Randomly choose a mode
    int prev_mode = TIFFSetMode(tif, mode);

    // Prepare a buffer for TIFFReadBufferSetup
    size_t buffer_size = (Size > 1024) ? 1024 : Size; // Limit buffer size
    void *buffer = malloc(buffer_size);
    if (buffer) {
        TIFFReadBufferSetup(tif, buffer, buffer_size);
        free(buffer);
    }

    // Retrieve file descriptor using TIFFFileno
    int file_no = TIFFFileno(tif);

    // Fuzz TIFFFlush
    TIFFFlush(tif);

    // Clean up
    TIFFClose(tif);
    close(fd);
    return 0;
}