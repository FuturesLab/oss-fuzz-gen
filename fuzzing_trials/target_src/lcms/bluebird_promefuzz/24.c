#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "lcms2.h"

static cmsHPROFILE createDummyProfile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsHPROFILE hProfile = createDummyProfile(Data, Size);
    if (!hProfile) {
        return 0;
    }

    // Test cmsGetHeaderRenderingIntent
    cmsUInt32Number renderingIntent = cmsGetHeaderRenderingIntent(hProfile);

    // Test cmsGetHeaderManufacturer
    cmsUInt32Number manufacturer = cmsGetHeaderManufacturer(hProfile);

    // Test cmsSetEncodedICCversion
    cmsUInt32Number version = *(cmsUInt32Number*)Data;
    cmsSetEncodedICCversion(hProfile, version);

    // Test cmsSetHeaderRenderingIntent
    cmsUInt32Number newRenderingIntent = *(cmsUInt32Number*)Data;
    cmsSetHeaderRenderingIntent(hProfile, newRenderingIntent);

    // Test cmsGetHeaderCreator
    cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);

    // Test cmsGetHeaderModel
    cmsUInt32Number model = cmsGetHeaderModel(hProfile);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsDetectDestinationBlackPoint
    int ret_cmsGetEncodedCMMversion_umzsz = cmsGetEncodedCMMversion();
    if (ret_cmsGetEncodedCMMversion_umzsz < 0){
    	return 0;
    }
    cmsCIEXYZ kafewiyi;
    memset(&kafewiyi, 0, sizeof(kafewiyi));

    cmsBool ret_cmsDetectDestinationBlackPoint_pifxj = cmsDetectDestinationBlackPoint(&kafewiyi, hProfile, 1, (unsigned long )ret_cmsGetEncodedCMMversion_umzsz);
    if (ret_cmsDetectDestinationBlackPoint_pifxj < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
    cmsMD5computeID(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}