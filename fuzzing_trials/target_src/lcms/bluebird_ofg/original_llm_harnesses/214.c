#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    // Initialize a cmsContext variable
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Call the function-under-test
    cmsIOHANDLER *handler = cmsOpenIOhandlerFromNULL(context);

    // Clean up
    if (handler != NULL) {
        cmsCloseIOhandler(handler);
    }
    cmsDeleteContext(context);

    return 0;
}