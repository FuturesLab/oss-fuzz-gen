// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateBCHSWabstractProfile at cmsvirt.c:946:32 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateLinearizationDeviceLink at cmsvirt.c:340:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateInkLimitingDeviceLink at cmsvirt.c:466:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsChannelsOfColorSpace at cmspcs.c:877:26 in lcms2.h
// cmsCreateLinearizationDeviceLinkTHR at cmsvirt.c:288:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateInkLimitingDeviceLinkTHR at cmsvirt.c:393:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lcms2.h>

static void fuzz_cmsCreateBCHSWabstractProfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number) + 2 * sizeof(cmsUInt32Number)) return;

    cmsUInt32Number nLUTPoints = *(cmsUInt32Number*)(Data);
    cmsFloat64Number Bright = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number));
    cmsFloat64Number Contrast = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number));
    cmsFloat64Number Hue = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 2 * sizeof(cmsFloat64Number));
    cmsFloat64Number Saturation = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 3 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempSrc = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempDest = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number) + sizeof(cmsUInt32Number));

    cmsHPROFILE hProfile = cmsCreateBCHSWabstractProfile(nLUTPoints, Bright, Contrast, Hue, Saturation, TempSrc, TempDest);
    if (hProfile) {
        cmsCloseProfile(hProfile);
    }
}

static void fuzz_cmsCreateLinearizationDeviceLink(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsColorSpaceSignature) + sizeof(cmsToneCurve*)) return;

    cmsColorSpaceSignature ColorSpace = *(cmsColorSpaceSignature*)(Data);
    cmsToneCurve* TransferFunctions[1] = { NULL }; // For simplicity, using a single NULL tone curve

    cmsHPROFILE hProfile = cmsCreateLinearizationDeviceLink(ColorSpace, TransferFunctions);
    if (hProfile) {
        cmsCloseProfile(hProfile);
    }
}

static void fuzz_cmsCreateInkLimitingDeviceLink(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsColorSpaceSignature) + sizeof(cmsFloat64Number)) return;

    cmsColorSpaceSignature ColorSpace = *(cmsColorSpaceSignature*)(Data);
    cmsFloat64Number Limit = *(cmsFloat64Number*)(Data + sizeof(cmsColorSpaceSignature));

    cmsHPROFILE hProfile = cmsCreateInkLimitingDeviceLink(ColorSpace, Limit);
    if (hProfile) {
        cmsCloseProfile(hProfile);
    }
}

static void fuzz_cmsChannelsOfColorSpace(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsColorSpaceSignature)) return;

    cmsColorSpaceSignature ColorSpace = *(cmsColorSpaceSignature*)(Data);

    cmsInt32Number channels = cmsChannelsOfColorSpace(ColorSpace);
}

static void fuzz_cmsCreateLinearizationDeviceLinkTHR(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsContext) + sizeof(cmsColorSpaceSignature) + sizeof(cmsToneCurve*)) return;

    cmsContext ContextID = *(cmsContext*)(Data);
    cmsColorSpaceSignature ColorSpace = *(cmsColorSpaceSignature*)(Data + sizeof(cmsContext));
    cmsToneCurve* TransferFunctions[1] = { NULL }; // For simplicity, using a single NULL tone curve

    cmsHPROFILE hProfile = cmsCreateLinearizationDeviceLinkTHR(ContextID, ColorSpace, TransferFunctions);
    if (hProfile) {
        cmsCloseProfile(hProfile);
    }
}

static void fuzz_cmsCreateInkLimitingDeviceLinkTHR(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsContext) + sizeof(cmsColorSpaceSignature) + sizeof(cmsFloat64Number)) return;

    cmsContext ContextID = *(cmsContext*)(Data);
    cmsColorSpaceSignature ColorSpace = *(cmsColorSpaceSignature*)(Data + sizeof(cmsContext));
    cmsFloat64Number Limit = *(cmsFloat64Number*)(Data + sizeof(cmsContext) + sizeof(cmsColorSpaceSignature));

    cmsHPROFILE hProfile = cmsCreateInkLimitingDeviceLinkTHR(ContextID, ColorSpace, Limit);
    if (hProfile) {
        cmsCloseProfile(hProfile);
    }
}

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    fuzz_cmsCreateBCHSWabstractProfile(Data, Size);
    fuzz_cmsCreateLinearizationDeviceLink(Data, Size);
    fuzz_cmsCreateInkLimitingDeviceLink(Data, Size);
    fuzz_cmsChannelsOfColorSpace(Data, Size);
    fuzz_cmsCreateLinearizationDeviceLinkTHR(Data, Size);
    fuzz_cmsCreateInkLimitingDeviceLinkTHR(Data, Size);

    return 0;
}