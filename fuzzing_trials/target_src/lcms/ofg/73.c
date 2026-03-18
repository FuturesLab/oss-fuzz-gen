#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Ensure the data size is not zero
    if (size == 0) {
        cmsDeleteContext(context);
        return 0;
    }

    // Allocate memory for the data buffer
    void *buffer = malloc(size);
    if (buffer == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Copy the input data to the buffer
    memcpy(buffer, data, size);

    // Use a non-NULL string for the last parameter
    const char *accessMode = "r";

    // Call the function-under-test
    cmsIOHANDLER *iohandler = cmsOpenIOhandlerFromMem(context, buffer, (cmsUInt32Number)size, accessMode);

    // Clean up
    if (iohandler != NULL) {
        cmsCloseIOhandler(iohandler);
    }
    free(buffer);
    cmsDeleteContext(context);

    return 0;
}