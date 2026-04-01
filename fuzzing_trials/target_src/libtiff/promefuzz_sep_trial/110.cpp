// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFFieldWithName at tif_dirinfo.c:941:18 in tiffio.h
// TIFFClientdata at tif_open.c:833:11 in tiffio.h
// TIFFSetClientInfo at tif_extension.c:78:6 in tiffio.h
// TIFFGetClientInfo at tif_extension.c:64:7 in tiffio.h
// TIFFSetFileName at tif_open.c:808:13 in tiffio.h
// TIFFFileName at tif_open.c:803:13 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <tiffio.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    writeDummyFile(Data, Size);
    
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    // Fuzz TIFFFieldWithName
    const char *fieldName = reinterpret_cast<const char *>(Data);
    const TIFFField *field = TIFFFieldWithName(tif, fieldName);

    // Fuzz TIFFClientdata
    thandle_t clientData = TIFFClientdata(tif);

    // Fuzz TIFFSetClientInfo and TIFFGetClientInfo
    TIFFSetClientInfo(tif, clientData, "testClientInfo");
    void *retrievedClientData = TIFFGetClientInfo(tif, "testClientInfo");

    // Fuzz TIFFSetFileName and TIFFFileName
    const char *prevFileName = TIFFSetFileName(tif, "new_file_name");
    const char *fileName = TIFFFileName(tif);

    TIFFClose(tif);

    return 0;
}