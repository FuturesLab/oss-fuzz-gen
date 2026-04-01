// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateBCHSWabstractProfileTHR at cmsvirt.c:861:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateBCHSWabstractProfile at cmsvirt.c:946:32 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateExtendedTransform at cmsxform.c:1123:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateTransform at cmsxform.c:1355:32 in lcms2.h
// cmsTransform2DeviceLink at cmsvirt.c:1194:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1398:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1286:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lcms2.h>

static cmsContext CreateDummyContext() {
    return NULL; // Simplified for fuzzing, normally you'd initialize a real context
}

static cmsHPROFILE CreateDummyProfile() {
    return NULL; // Simplified for fuzzing, normally you'd create a real profile
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 7 + sizeof(cmsFloat64Number) * 4) {
        return 0; // Not enough data to proceed
    }

    cmsContext context = CreateDummyContext();
    cmsUInt32Number nLUTPoints = *(cmsUInt32Number *)Data;
    cmsFloat64Number Bright = *(cmsFloat64Number *)(Data + sizeof(cmsUInt32Number));
    cmsFloat64Number Contrast = *(cmsFloat64Number *)(Data + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number));
    cmsFloat64Number Hue = *(cmsFloat64Number *)(Data + sizeof(cmsUInt32Number) + 2 * sizeof(cmsFloat64Number));
    cmsFloat64Number Saturation = *(cmsFloat64Number *)(Data + sizeof(cmsUInt32Number) + 3 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempSrc = *(cmsUInt32Number *)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempDest = *(cmsUInt32Number *)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number) + sizeof(cmsUInt32Number));

    // Fuzz cmsCreateBCHSWabstractProfileTHR
    cmsHPROFILE profile1 = cmsCreateBCHSWabstractProfileTHR(context, nLUTPoints, Bright, Contrast, Hue, Saturation, TempSrc, TempDest);
    if (profile1) {
        cmsCloseProfile(profile1);
    }

    // Fuzz cmsCreateBCHSWabstractProfile
    cmsHPROFILE profile2 = cmsCreateBCHSWabstractProfile(nLUTPoints, Bright, Contrast, Hue, Saturation, TempSrc, TempDest);
    if (profile2) {
        cmsCloseProfile(profile2);
    }

    // Fuzz cmsCreateExtendedTransform
    cmsHPROFILE hProfiles[2] = {CreateDummyProfile(), CreateDummyProfile()};
    cmsBool BPC[2] = {0, 0};
    cmsUInt32Number Intents[2] = {0, 0};
    cmsFloat64Number AdaptationStates[2] = {0.0, 0.0};
    cmsHTRANSFORM transform1 = cmsCreateExtendedTransform(context, 2, hProfiles, BPC, Intents, AdaptationStates, NULL, 0, 0, 0, 0);
    if (transform1) {
        cmsDeleteTransform(transform1);
    }

    // Fuzz cmsTransform2DeviceLink
    cmsHTRANSFORM transform2 = cmsCreateTransform(hProfiles[0], 0, hProfiles[1], 0, 0, 0);
    if (transform2) {
        cmsHPROFILE deviceLink = cmsTransform2DeviceLink(transform2, 4.3, 0);
        if (deviceLink) {
            cmsCloseProfile(deviceLink);
        }
        cmsDeleteTransform(transform2);
    }

    // Fuzz cmsCreateProofingTransform
    cmsHTRANSFORM transform3 = cmsCreateProofingTransform(hProfiles[0], 0, hProfiles[1], 0, hProfiles[0], 0, 0, 0);
    if (transform3) {
        cmsDeleteTransform(transform3);
    }

    // Fuzz cmsCreateMultiprofileTransformTHR
    cmsHTRANSFORM transform4 = cmsCreateMultiprofileTransformTHR(context, hProfiles, 2, 0, 0, 0, 0);
    if (transform4) {
        cmsDeleteTransform(transform4);
    }

    return 0;
}