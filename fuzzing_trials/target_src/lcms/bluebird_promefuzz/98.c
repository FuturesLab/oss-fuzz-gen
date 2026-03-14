#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void fuzz_cmsGetHeaderAttributes(cmsHPROFILE hProfile) {
    cmsUInt64Number Flags;
    cmsGetHeaderAttributes(hProfile, &Flags);
}

static void fuzz_cmsSetHeaderAttributes(cmsHPROFILE hProfile) {
    cmsUInt64Number Flags = rand();
    cmsSetHeaderAttributes(hProfile, Flags);
}

static void fuzz_cmsGetEncodedICCversion(cmsHPROFILE hProfile) {
    cmsUInt32Number version = cmsGetEncodedICCversion(hProfile);
}

static void fuzz_cmsSetEncodedICCversion(cmsHPROFILE hProfile) {
    cmsUInt32Number version = rand();
    cmsSetEncodedICCversion(hProfile, version);
}

static void fuzz_cmsSetHeaderModel(cmsHPROFILE hProfile) {
    cmsUInt32Number model = rand();
    cmsSetHeaderModel(hProfile, model);
}

static void fuzz_cmsSetHeaderManufacturer(cmsHPROFILE hProfile) {
    cmsUInt32Number manufacturer = rand();
    cmsSetHeaderManufacturer(hProfile, manufacturer);
}

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    if (hProfile == NULL) {
        return 0;
    }

    fuzz_cmsGetHeaderAttributes(hProfile);
    fuzz_cmsSetHeaderAttributes(hProfile);
    fuzz_cmsGetEncodedICCversion(hProfile);
    fuzz_cmsSetEncodedICCversion(hProfile);
    fuzz_cmsSetHeaderModel(hProfile);
    fuzz_cmsSetHeaderManufacturer(hProfile);

    cmsCloseProfile(hProfile);
    return 0;
}