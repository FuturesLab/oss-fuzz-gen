#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsMLU *mlu = NULL;
    cmsMLU *duplicatedMlu = NULL;
    cmsContext contextID = NULL;
    const char *languageCode = "en";
    const char *countryCode = "US";
    const char *text = "Sample text";

    // Create a cmsMLU object
    mlu = cmsMLUalloc(contextID, 1);

    // Check if mlu was successfully allocated
    if (mlu == NULL) {
        return 0;
    }

    // Set a simple text entry to the cmsMLU object
    if (!cmsMLUsetASCII(mlu, languageCode, countryCode, text)) {
        cmsMLUfree(mlu);
        return 0;
    }

    // Call the function-under-test
    duplicatedMlu = cmsMLUdup(mlu);

    // Free the original cmsMLU object
    cmsMLUfree(mlu);

    // Free the duplicated cmsMLU object if it was successfully created
    if (duplicatedMlu != NULL) {
        cmsMLUfree(duplicatedMlu);
    }

    return 0;
}