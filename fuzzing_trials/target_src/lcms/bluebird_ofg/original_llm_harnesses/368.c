#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_368(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsHPROFILE profile = NULL;

    if (size < 3) { // Ensure there is enough data for both filename and mode
        cmsDeleteContext(context);
        return 0;
    }

    // Creating a null-terminated string for the file name and mode
    char filename[256];
    char mode[4];

    size_t filename_len = size > 255 ? 255 : size - 3; // Ensure space for mode
    size_t mode_len = 3; // We need exactly 3 characters for mode

    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    memcpy(mode, data + filename_len, mode_len);
    mode[mode_len] = '\0';

    // Call the function-under-test
    profile = cmsOpenProfileFromFileTHR(context, filename, mode);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}