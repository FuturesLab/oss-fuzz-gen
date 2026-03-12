#include <stdint.h>
#include <string.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsInfoType infoType;
    const char *languageCode = "en";
    const char *countryCode = "US";
    char buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer);

    // Ensure the data size is sufficient for creating a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Initialize the profile handle from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Iterate over possible infoType values
    for (int i = 0; i < 6; i++) {
        infoType = (cmsInfoType)i;

        // Call the function-under-test
        cmsGetProfileInfoUTF8(hProfile, infoType, languageCode, countryCode, buffer, bufferSize);
    }

    // Close the profile handle

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetProfileInfoUTF8 to cmsIT8SetData
        cmsHANDLE ret_cmsIT8Alloc_hyacm = cmsIT8Alloc(0);


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsIT8Alloc to cmsIT8DefineDblFormat

        cmsIT8DefineDblFormat(ret_cmsIT8Alloc_hyacm, NULL);

        // End mutation: Producer.APPEND_MUTATOR

        cmsBool ret_cmsIT8SetData_qcams = cmsIT8SetData(ret_cmsIT8Alloc_hyacm, buffer, (const char *)"w", (const char *)data);
        if (ret_cmsIT8SetData_qcams < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    cmsCloseProfile(hProfile);

    return 0;
}