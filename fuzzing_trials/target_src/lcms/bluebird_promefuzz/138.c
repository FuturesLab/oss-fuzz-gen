#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static cmsHPROFILE LoadProfileFromMemory(const uint8_t *Data, size_t Size) {
    // Create a temporary file to simulate reading from a file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        return NULL;
    }

    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Open the profile from the file
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    cmsHPROFILE hProfile = LoadProfileFromMemory(Data, Size);
    if (!hProfile) {
        return 0;
    }

    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    if (tagCount > 0) {
        for (cmsUInt32Number i = 0; i < (cmsUInt32Number)tagCount; i++) {

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsGetTagSignature
            cmsTagSignature sig = cmsGetTagSignature(hProfile, FALSE);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


            if (sig != 0) {
                void *tagData = cmsReadTag(hProfile, sig);
                // Normally you would do something with tagData, but we just test the call
            }
        }
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsSetColorSpace
    cmsColorSpaceSignature ret__cmsICCcolorSpace_fadnw = _cmsICCcolorSpace(cmsERROR_CORRUPTION_DETECTED);

    cmsSetColorSpace(hProfile, ret__cmsICCcolorSpace_fadnw);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsSetEncodedICCversion

    cmsSetEncodedICCversion(hProfile, cmsD50X);

    // End mutation: Producer.APPEND_MUTATOR

    cmsMD5computeID(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}