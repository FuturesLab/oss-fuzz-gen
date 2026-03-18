// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetClientdata at tif_open.c:838:11 in tiffio.h
// TIFFClientdata at tif_open.c:833:11 in tiffio.h
// TIFFSetClientInfo at tif_extension.c:78:6 in tiffio.h
// TIFFGetClientInfo at tif_extension.c:64:7 in tiffio.h
// TIFFFieldWithName at tif_dirinfo.c:941:18 in tiffio.h
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
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *Data, size_t Size) {
    // Create a dummy TIFF object
    TIFF *tif = TIFFOpen("./dummy_file", "w");

    if (!tif) {
        return 0;
    }

    // Create a buffer to store client data
    char clientData[256] = {0};
    if (Size > 0) {
        std::memcpy(clientData, Data, Size < 255 ? Size : 255);
    }

    // Set client data
    thandle_t oldClientData = TIFFSetClientdata(tif, static_cast<thandle_t>(clientData));

    // Retrieve client data
    thandle_t retrievedClientData = TIFFClientdata(tif);

    // Set client info
    TIFFSetClientInfo(tif, static_cast<void *>(clientData), "testClientInfo");

    // Retrieve client info
    void *retrievedClientInfo = TIFFGetClientInfo(tif, "testClientInfo");

    // Attempt to retrieve a field by name
    const TIFFField *field = TIFFFieldWithName(tif, "testField");

    // Close the TIFF file (this will also perform cleanup)
    TIFFClose(tif);

    return 0;
}