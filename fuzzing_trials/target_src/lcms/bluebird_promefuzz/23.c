#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static cmsHPROFILE createDummyProfile() {
    // Create a simple RGB profile for testing
    return cmsCreateRGBProfile(NULL, NULL, NULL);
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsTagSignature)) {
        return 0;
    }

    cmsHPROFILE hProfile = createDummyProfile();
    if (!hProfile) {
        return 0;
    }

    cmsTagSignature sig = *(cmsTagSignature*)Data;
    const char dummyLang[3] = "en";
    const char dummyCountry[3] = "US";
    wchar_t infoBuffer[256];
    char rawBuffer[256];

    // Fuzz cmsReadTag
    void* tagData = cmsReadTag(hProfile, sig);

    // Fuzz cmsReadRawTag
    cmsUInt32Number rawSize = cmsReadRawTag(hProfile, sig, rawBuffer, sizeof(rawBuffer));

    // Fuzz cmsGetProfileInfo
    cmsUInt32Number infoSize = cmsGetProfileInfo(hProfile, 0, dummyLang, dummyCountry, infoBuffer, sizeof(infoBuffer) / sizeof(wchar_t));

    // Fuzz cmsGetTagCount
    cmsInt32Number tagCount = cmsGetTagCount(hProfile);

    // Fuzz cmsGetTagSignature
    if (tagCount > 0) {
        for (cmsUInt32Number i = 0; i < (cmsUInt32Number)tagCount; i++) {
            cmsTagSignature tagSig = cmsGetTagSignature(hProfile, i);
        }
    }

    // Clean up
    cmsBool closeResult = cmsCloseProfile(hProfile);

    return 0;
}