#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract meaningful strings
    if (size < 4) {
        return 0;
    }

    // Create a dummy cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Extract two strings from the input data
    size_t len1 = data[0] % (size - 2) + 1;
    size_t len2 = data[1] % (size - len1 - 1) + 1;

    char *filename = (char *)malloc(len1 + 1);
    char *mode = (char *)malloc(len2 + 1);

    if (filename == NULL || mode == NULL) {
        free(filename);
        free(mode);
        cmsDeleteContext(context);
        return 0;
    }

    memcpy(filename, data + 2, len1);
    filename[len1] = '\0';

    memcpy(mode, data + 2 + len1, len2);
    mode[len2] = '\0';

    // Call the function under test
    cmsIOHANDLER *handler = cmsOpenIOhandlerFromFile(context, filename, mode);

    // Clean up
    if (handler != NULL) {
        cmsCloseIOhandler(handler);
    }
    free(filename);
    free(mode);
    cmsDeleteContext(context);

    return 0;
}