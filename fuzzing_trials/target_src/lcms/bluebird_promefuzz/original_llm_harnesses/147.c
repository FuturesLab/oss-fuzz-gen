// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateNULLProfile at cmsvirt.c:1018:23 in lcms2.h
// cmsLinkTag at cmsio0.c:2071:19 in lcms2.h
// cmsGetEncodedICCversion at cmsio0.c:1106:27 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:997:27 in lcms2.h
// cmsGetDeviceClass at cmsio0.c:1094:36 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1027:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <lcms2.h>

static cmsTagSignature randomTagSignature(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsTagSignature)) return 0;
    cmsTagSignature sig;
    memcpy(&sig, data, sizeof(cmsTagSignature));
    return sig;
}

int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a NULL profile for testing
    cmsHPROFILE hProfile = cmsCreateNULLProfile();
    if (!hProfile) return 0;

    // Test cmsLinkTag
    if (Size >= 2 * sizeof(cmsTagSignature)) {
        cmsTagSignature sig = randomTagSignature(Data, Size);
        cmsTagSignature dest = randomTagSignature(Data + sizeof(cmsTagSignature), Size - sizeof(cmsTagSignature));
        cmsLinkTag(hProfile, sig, dest);
    }

    // Test cmsGetEncodedICCversion
    cmsUInt32Number version = cmsGetEncodedICCversion(hProfile);

    // Test cmsGetHeaderFlags
    cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);

    // Test cmsGetDeviceClass
    cmsProfileClassSignature deviceClass = cmsGetDeviceClass(hProfile);

    // Test cmsGetHeaderModel
    cmsUInt32Number model = cmsGetHeaderModel(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}