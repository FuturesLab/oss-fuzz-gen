#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
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
        cmsCloseProfile(profile);
    }

    return 0;
}