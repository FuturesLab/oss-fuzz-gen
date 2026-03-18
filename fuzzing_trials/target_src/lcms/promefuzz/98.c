// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsSetProfileVersion at cmsio0.c:1139:17 in lcms2.h
// cmsGetProfileVersion at cmsio0.c:1148:28 in lcms2.h
// cmsSetDeviceClass at cmsio0.c:1100:16 in lcms2.h
// cmsGetDeviceClass at cmsio0.c:1094:36 in lcms2.h
// cmsDetectRGBProfileGamma at cmsgmt.c:605:28 in lcms2.h
// cmsDetectTAC at cmsgmt.c:462:28 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "lcms2.h"

static cmsHPROFILE createDummyProfile() {
    // Create a dummy ICC profile for testing
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    if (!hProfile) {
        FILE *file = fopen("./dummy_file", "wb");
        if (file) {
            // Write some dummy content to simulate an ICC profile
            const char dummyContent[128] = {0};
            fwrite(dummyContent, 1, sizeof(dummyContent), file);
            fclose(file);
            hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
        }
    }
    return hProfile;
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number) + sizeof(cmsProfileClassSignature)) {
        return 0;
    }

    cmsHPROFILE hProfile = createDummyProfile();
    if (!hProfile) {
        return 0;
    }

    cmsFloat64Number version = *(cmsFloat64Number *)Data;
    cmsProfileClassSignature sig = *(cmsProfileClassSignature *)(Data + sizeof(cmsFloat64Number));
    cmsFloat64Number threshold = *(cmsFloat64Number *)(Data + sizeof(cmsFloat64Number) + sizeof(cmsProfileClassSignature));

    // Test cmsSetProfileVersion
    cmsSetProfileVersion(hProfile, version);

    // Test cmsGetProfileVersion
    cmsFloat64Number retrievedVersion = cmsGetProfileVersion(hProfile);

    // Test cmsSetDeviceClass
    cmsSetDeviceClass(hProfile, sig);

    // Test cmsGetDeviceClass
    cmsProfileClassSignature retrievedSig = cmsGetDeviceClass(hProfile);

    // Test cmsDetectRGBProfileGamma
    cmsFloat64Number gamma = cmsDetectRGBProfileGamma(hProfile, threshold);

    // Test cmsDetectTAC
    cmsFloat64Number tac = cmsDetectTAC(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}