#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nIntents = 0;
    char *description = NULL;

    // Ensure that size is large enough to extract a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Use the first part of the data as the intent
    cmsUInt32Number intent = *(const cmsUInt32Number *)data;

    // Check if the intent is within a reasonable range
    if (intent >= INTENT_PERCEPTUAL && intent <= INTENT_ABSOLUTE_COLORIMETRIC) {
        // Ensure that nIntents and description are valid pointers before calling the function
        if (cmsGetSupportedIntentsTHR(context, intent, &nIntents, &description)) {
            // Process the result if needed
        }
    }

    // Clean up
    if (description != NULL) {
        free(description);
    }
    cmsDeleteContext(context);

    return 0;
}