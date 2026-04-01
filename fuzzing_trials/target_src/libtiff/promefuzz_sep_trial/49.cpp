// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
// TIFFSetClientdata at tif_open.c:838:11 in tiffio.h
// TIFFClientdata at tif_open.c:833:11 in tiffio.h
// TIFFReadBufferSetup at tif_read.c:1385:5 in tiffio.h
// TIFFGetSizeProc at tif_open.c:937:14 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetErrorHandlerExtR at tif_open.c:121:6 in tiffio.h
// TIFFOpenOptionsSetMaxSingleMemAlloc at tif_open.c:94:6 in tiffio.h
// TIFFOpenOptionsSetWarnAboutUnknownTags at tif_open.c:115:6 in tiffio.h
// TIFFClientOpenExt at tif_open.c:300:7 in tiffio.h
// TIFFSetClientdata at tif_open.c:838:11 in tiffio.h
// TIFFClientdata at tif_open.c:833:11 in tiffio.h
// TIFFReadBufferSetup at tif_read.c:1385:5 in tiffio.h
// TIFFGetSizeProc at tif_open.c:937:14 in tiffio.h
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
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static tmsize_t dummyReadProc(thandle_t, void*, tmsize_t) {
    return 0;
}

static tmsize_t dummyWriteProc(thandle_t, void*, tmsize_t) {
    return 0;
}

static toff_t dummySeekProc(thandle_t, toff_t, int) {
    return 0;
}

static int dummyCloseProc(thandle_t) {
    return 0;
}

static toff_t dummySizeProc(thandle_t) {
    return 0;
}

static int dummyMapFileProc(thandle_t, void**, toff_t*) {
    return 0;
}

static void dummyUnmapFileProc(thandle_t, void*, toff_t) {
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    FILE* file = std::fopen("./dummy_file", "wb");
    if (!file) return 0;
    std::fwrite(Data, 1, Size, file);
    std::fclose(file);

    // Open TIFF using TIFFClientOpen
    TIFF* tif = TIFFClientOpen("dummy", "r", nullptr, dummyReadProc, dummyWriteProc,
                               dummySeekProc, dummyCloseProc, dummySizeProc,
                               dummyMapFileProc, dummyUnmapFileProc);
    if (tif) {
        // Set client data
        thandle_t oldClientData = TIFFSetClientdata(tif, (thandle_t)Data);
        
        // Retrieve client data
        thandle_t clientData = TIFFClientdata(tif);

        // Set up read buffer
        int bufferSetupResult = TIFFReadBufferSetup(tif, nullptr, 1024);

        // Get size procedure
        TIFFSizeProc sizeProc = TIFFGetSizeProc(tif);

        // Close TIFF
        TIFFClose(tif);
    }

    // Open TIFF using TIFFClientOpenExt
    TIFFOpenOptions* opts = TIFFOpenOptionsAlloc();
    TIFFOpenOptionsSetErrorHandlerExtR(opts, nullptr, nullptr);
    TIFFOpenOptionsSetMaxSingleMemAlloc(opts, 0);
    TIFFOpenOptionsSetWarnAboutUnknownTags(opts, 0);

    TIFF* tifExt = TIFFClientOpenExt("dummy", "r", nullptr, dummyReadProc, dummyWriteProc,
                                     dummySeekProc, dummyCloseProc, dummySizeProc,
                                     dummyMapFileProc, dummyUnmapFileProc, opts);
    if (tifExt) {
        // Set client data
        thandle_t oldClientDataExt = TIFFSetClientdata(tifExt, (thandle_t)Data);

        // Retrieve client data
        thandle_t clientDataExt = TIFFClientdata(tifExt);

        // Set up read buffer
        int bufferSetupResultExt = TIFFReadBufferSetup(tifExt, nullptr, 1024);

        // Get size procedure
        TIFFSizeProc sizeProcExt = TIFFGetSizeProc(tifExt);

        // Close TIFF
        TIFFClose(tifExt);
    }

    TIFFOpenOptionsFree(opts);

    return 0;
}