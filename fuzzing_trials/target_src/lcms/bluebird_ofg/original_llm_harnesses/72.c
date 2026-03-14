#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free
#include <lcms2.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Allocate memory for the handler
    void *memory = malloc(size);
    if (memory == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Copy the input data to the allocated memory
    memcpy(memory, data, size);

    // Define a non-NULL string for the 'const char *' parameter
    const char *mode = "r";

    // Call the function-under-test
    cmsIOHANDLER *handler = cmsOpenIOhandlerFromMem(context, memory, (cmsUInt32Number)size, mode);

    // Perform cleanup
    if (handler != NULL) {
        cmsCloseIOhandler(handler);
    }
    free(memory);
    cmsDeleteContext(context);

    return 0;
}