#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for null-terminated strings
    if (size < 3) {
        return 0;
    }

    // Allocate memory for the file name and mode strings
    char filename[2];
    char mode[2];

    // Copy the first byte to filename and ensure null-termination
    filename[0] = (char)data[0];
    filename[1] = '\0';

    // Copy the second byte to mode and ensure null-termination
    mode[0] = (char)data[1];
    mode[1] = '\0';

    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromFile(filename, mode);

    // If a valid profile was returned, close it
    if (profile != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsGetProfileInfoASCII

    cmsUInt32Number ret_cmsGetProfileInfoASCII_cdqix = cmsGetProfileInfoASCII(profile, 0, (const char *)"r", (const char *)"r", NULL, cmsERROR_SEEK);
    if (ret_cmsGetProfileInfoASCII_cdqix < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        cmsCloseProfile(profile);
    }
    return 0;
}