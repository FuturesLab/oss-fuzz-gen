// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFFieldWithTag at tif_dirinfo.c:930:18 in tiffio.h
// TIFFGetTagListEntry at tif_extension.c:42:10 in tiffio.h
// TIFFUnsetField at tif_dir.c:1166:5 in tiffio.h
// TIFFFindField at tif_dirinfo.c:878:18 in tiffio.h
// TIFFFieldTag at tif_dirinfo.c:952:10 in tiffio.h
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
#include <cstdarg>
#include <vector>
#include <fstream>

static TIFF* openDummyTIFF(const uint8_t* Data, size_t Size) {
    std::ofstream ofs("./dummy_file", std::ios::binary);
    if (!ofs) {
        return nullptr;
    }
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();

    return TIFFOpen("./dummy_file", "r");
}

static void closeTIFF(TIFF* tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for a tag

    TIFF* tif = openDummyTIFF(Data, Size);
    if (!tif) return 0;

    // Extract a tag from the input data
    uint32_t tag = *reinterpret_cast<const uint32_t*>(Data);

    // Fuzz TIFFGetField
    uint32_t value;
    TIFFGetField(tif, tag, &value);

    // Fuzz TIFFFieldWithTag
    const TIFFField* field = TIFFFieldWithTag(tif, tag);

    // Fuzz TIFFGetTagListEntry
    int tag_index = tag % static_cast<int>(Size); // Ensure tag_index is within bounds
    uint32_t tag_value = TIFFGetTagListEntry(tif, tag_index);

    // Fuzz TIFFUnsetField
    TIFFUnsetField(tif, tag);

    // Fuzz TIFFFindField
    TIFFDataType dataType = static_cast<TIFFDataType>(tag % 10); // Randomly choose a data type
    const TIFFField* foundField = TIFFFindField(tif, tag, dataType);

    // Fuzz TIFFFieldTag
    if (field) {
        uint32_t fieldTag = TIFFFieldTag(field);
    }

    closeTIFF(tif);
    return 0;
}