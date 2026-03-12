#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static cmsHPROFILE LoadProfileFromData(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }
    
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_160(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    cmsHPROFILE hProfile = LoadProfileFromData(Data, Size);
    if (!hProfile) {
        return 0;
    }

    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    if (tagCount > 0) {
        for (cmsUInt32Number i = 0; i < (cmsUInt32Number)tagCount; i++) {
            cmsTagSignature tagSig = cmsGetTagSignature(hProfile, i);
            if (tagSig != 0) {
                cmsUInt32Number bufferSize = 1024; // Arbitrary buffer size
                void *buffer = malloc(bufferSize);
                if (buffer) {

                    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsReadRawTag
                    cmsReadRawTag(hProfile, tagSig, NULL, bufferSize);
                    // End mutation: Producer.REPLACE_ARG_MUTATOR


                    free(buffer);
                }
            }
        }
    }

    cmsCloseProfile(hProfile);
    return 0;
}