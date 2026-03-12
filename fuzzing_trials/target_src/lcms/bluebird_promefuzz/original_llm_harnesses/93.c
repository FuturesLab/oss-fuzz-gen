// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsEncodeDateTimeNumber at cmsplugin.c:407:16 in lcms2_plugin.h
// _cmsDecodeDateTimeNumber at cmsplugin.c:390:16 in lcms2_plugin.h
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
// cmsGetHeaderCreationDateTime at cmsio0.c:1063:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
// cmsGetHeaderAttributes at cmsio0.c:1039:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// _cmsAdjustEndianess64 at cmsplugin.c:79:17 in lcms2_plugin.h
// _cmsReadUInt64Number at cmsplugin.c:206:21 in lcms2_plugin.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static void fuzz_cmsEncodeDecodeDateTimeNumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct tm)) return;

    struct tm source_tm;
    cmsDateTimeNumber dest_dt;

    // Copy data into source_tm ensuring it doesn't exceed its size
    memcpy(&source_tm, Data, sizeof(struct tm));

    _cmsEncodeDateTimeNumber(&dest_dt, &source_tm);

    struct tm decoded_tm;
    _cmsDecodeDateTimeNumber(&dest_dt, &decoded_tm);
}

static void fuzz_cmsGetHeaderCreationDateTime(const uint8_t *Data, size_t Size) {
    // Ensure we have enough data to simulate a valid profile handle
    if (Size < sizeof(cmsHPROFILE)) return;

    // Create a dummy ICC profile for testing
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return;

    struct tm dest_tm;
    cmsGetHeaderCreationDateTime(hProfile, &dest_tm);

    // Close the profile to avoid memory leaks
    cmsCloseProfile(hProfile);
}

static void fuzz_cmsGetHeaderAttributes(const uint8_t *Data, size_t Size) {
    // Ensure we have enough data to simulate a valid profile handle
    if (Size < sizeof(cmsHPROFILE)) return;

    // Create a dummy ICC profile for testing
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return;

    cmsUInt64Number flags;
    cmsGetHeaderAttributes(hProfile, &flags);

    // Close the profile to avoid memory leaks
    cmsCloseProfile(hProfile);
}

static void fuzz_cmsAdjustEndianess64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt64Number)) return;

    cmsUInt64Number qword, result;

    memcpy(&qword, Data, sizeof(cmsUInt64Number));

    _cmsAdjustEndianess64(&result, &qword);
}

static void fuzz_cmsReadUInt64Number(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsIOHANDLER) + sizeof(cmsUInt64Number)) return;

    cmsIOHANDLER io;
    cmsUInt64Number number;

    memcpy(&io, Data, sizeof(cmsIOHANDLER));

    _cmsReadUInt64Number(&io, &number);
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    fuzz_cmsEncodeDecodeDateTimeNumber(Data, Size);
    fuzz_cmsGetHeaderCreationDateTime(Data, Size);
    fuzz_cmsGetHeaderAttributes(Data, Size);
    fuzz_cmsAdjustEndianess64(Data, Size);
    fuzz_cmsReadUInt64Number(Data, Size);

    return 0;
}