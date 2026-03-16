#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"

static TIFF* initialize_tiff(const uint8_t* Data, size_t Size) {
    FILE* file = std::fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    std::fwrite(Data, 1, Size, file);
    std::fclose(file);

    TIFF* tiff = TIFFOpen("./dummy_file", "r+");
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tdir_t) * 3 + sizeof(uint32_t)) return 0;

    TIFF* tiff = initialize_tiff(Data, Size);
    if (!tiff) return 0;

    tdir_t dir1 = *reinterpret_cast<const tdir_t*>(Data);
    tdir_t dir2 = *reinterpret_cast<const tdir_t*>(Data + sizeof(tdir_t));
    tdir_t dir3 = *reinterpret_cast<const tdir_t*>(Data + 2 * sizeof(tdir_t));
    uint32_t longValue = *reinterpret_cast<const uint32_t*>(Data + 3 * sizeof(tdir_t));

    TIFFSetDirectory(tiff, dir1);
    TIFFSetDirectory(tiff, dir2);
    TIFFCurrentDirOffset(tiff);
    TIFFGetSeekProc(tiff);
    TIFFIsByteSwapped(tiff);
    TIFFSwabLong(&longValue);
    TIFFGetWriteProc(tiff);
    TIFFNumberOfDirectories(tiff);
    TIFFSetDirectory(tiff, dir3);
    TIFFSetDirectory(tiff, dir1);

    TIFFClose(tiff);
    tiff = nullptr; // Prevent further operations on freed memory

    return 0;
}