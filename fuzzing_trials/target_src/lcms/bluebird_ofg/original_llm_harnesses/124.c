#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsMLU *mlu;
    const char *language = "en";
    const char *country = "US";
    char outputBuffer[256];
    cmsUInt32Number bufferSize = sizeof(outputBuffer);

    // Create a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a cmsMLU object
    mlu = cmsMLUalloc(contextID, 1);

    // Check if mlu allocation was successful
    if (mlu == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Set some dummy data into the cmsMLU object
    cmsMLUsetASCII(mlu, language, country, "Test String");

    // Call the function-under-test
    cmsUInt32Number result = cmsMLUgetUTF8(mlu, language, country, outputBuffer, bufferSize);

    // Clean up
    cmsMLUfree(mlu);
    cmsDeleteContext(contextID);

    return 0;
}