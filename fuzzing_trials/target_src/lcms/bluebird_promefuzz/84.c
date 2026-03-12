#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcms2.h"

static void fuzz_cmsCreateBCHSWabstractProfileTHR(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * 4) {
        return;
    }

    cmsContext ContextID = NULL;
    cmsUInt32Number nLUTPoints = *(cmsUInt32Number*)Data;
    cmsFloat64Number Bright = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number));
    cmsFloat64Number Contrast = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number));
    cmsFloat64Number Hue = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 2 * sizeof(cmsFloat64Number));
    cmsFloat64Number Saturation = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 3 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempSrc = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempDest = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));

    cmsHPROFILE profile = cmsCreateBCHSWabstractProfileTHR(ContextID, nLUTPoints, Bright, Contrast, Hue, Saturation, TempSrc, TempDest);
    if (profile) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
        cmsMD5computeID(profile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
}

static void fuzz_cmsCreateBCHSWabstractProfile(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * 4) {
        return;
    }

    cmsUInt32Number nLUTPoints = *(cmsUInt32Number*)Data;
    cmsFloat64Number Bright = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number));
    cmsFloat64Number Contrast = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + sizeof(cmsFloat64Number));
    cmsFloat64Number Hue = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 2 * sizeof(cmsFloat64Number));
    cmsFloat64Number Saturation = *(cmsFloat64Number*)(Data + sizeof(cmsUInt32Number) + 3 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempSrc = *(cmsUInt32Number*)(Data + sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));
    cmsUInt32Number TempDest = *(cmsUInt32Number*)(Data + 2 * sizeof(cmsUInt32Number) + 4 * sizeof(cmsFloat64Number));

    cmsHPROFILE profile = cmsCreateBCHSWabstractProfile(nLUTPoints, Bright, Contrast, Hue, Saturation, TempSrc, TempDest);
    if (profile) {
        cmsCloseProfile(profile);
    }
}

static void fuzz_cmsCreateExtendedTransform(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 7 + sizeof(cmsFloat64Number)) {
        return;
    }

    cmsContext ContextID = NULL;
    cmsUInt32Number nProfiles = Data[0] % 256; // Ensuring nProfiles is between 1 and 255
    cmsHPROFILE hProfiles[256] = {0};
    cmsBool BPC[256] = {0};
    cmsUInt32Number Intents[256] = {0};
    cmsFloat64Number AdaptationStates[256] = {0.0};
    cmsHPROFILE hGamutProfile = NULL;
    cmsUInt32Number nGamutPCSposition = *(cmsUInt32Number*)(Data + 1);
    cmsUInt32Number InputFormat = *(cmsUInt32Number*)(Data + 1 + sizeof(cmsUInt32Number));
    cmsUInt32Number OutputFormat = *(cmsUInt32Number*)(Data + 1 + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + 1 + 3 * sizeof(cmsUInt32Number));

    cmsHTRANSFORM transform = cmsCreateExtendedTransform(ContextID, nProfiles, hProfiles, BPC, Intents, AdaptationStates, hGamutProfile, nGamutPCSposition, InputFormat, OutputFormat, dwFlags);
    if (transform) {
        cmsDeleteTransform(transform);
    }
}

static void fuzz_cmsTransform2DeviceLink(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number) + sizeof(cmsUInt32Number)) {
        return;
    }

    cmsHTRANSFORM hTransform = cmsCreateTransform(NULL, TYPE_RGB_8, NULL, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (!hTransform) {
        return;
    }

    cmsFloat64Number Version = *(cmsFloat64Number*)Data;
    cmsUInt32Number dwFlags = *(cmsUInt32Number*)(Data + sizeof(cmsFloat64Number));

    cmsHPROFILE profile = cmsTransform2DeviceLink(hTransform, Version, dwFlags);
    if (profile) {
        cmsCloseProfile(profile);
    }

    cmsDeleteTransform(hTransform);
}

static void fuzz_cmsSetAdaptationState(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) {
        return;
    }

    cmsFloat64Number d = *(cmsFloat64Number*)Data;
    cmsSetAdaptationState(d);
}

static void fuzz_cmsSetProfileVersion(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) {
        return;
    }

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile(); // Create a valid profile to avoid NULL pointer dereference
    if (!hProfile) {
        return;
    }

    cmsFloat64Number Version = *(cmsFloat64Number*)Data;
    cmsSetProfileVersion(hProfile, Version);

    cmsCloseProfile(hProfile);
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    fuzz_cmsCreateBCHSWabstractProfileTHR(Data, Size);
    fuzz_cmsCreateBCHSWabstractProfile(Data, Size);
    fuzz_cmsCreateExtendedTransform(Data, Size);
    fuzz_cmsTransform2DeviceLink(Data, Size);
    fuzz_cmsSetAdaptationState(Data, Size);
    fuzz_cmsSetProfileVersion(Data, Size);

    return 0;
}