#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for meaningful operations
    if (size < 3) {
        return 0;
    }

    // Allocate and initialize the original cmsMLU object
    cmsMLU *originalMlu = cmsMLUalloc(NULL, 1);

    // Check if the originalMlu allocation was successful
    if (originalMlu == NULL) {
        return 0;
    }

    // Use the input data to set the language and country codes, and a string
    char langCode[3] = { data[0], data[1], '\0' };
    char countryCode[3] = { data[2], data[3], '\0' };
    const char *stringData = (const char *)(data + 4);
    size_t stringLength = size - 4;

    // Ensure the string data is null-terminated
    char *nullTerminatedString = (char *)malloc(stringLength + 1);
    if (nullTerminatedString == NULL) {
        cmsMLUfree(originalMlu);
        return 0;
    }
    memcpy(nullTerminatedString, stringData, stringLength);
    nullTerminatedString[stringLength] = '\0';

    // Populate the cmsMLU object with the fuzzed data
    cmsMLUsetASCII(originalMlu, langCode, countryCode, nullTerminatedString);

    // Call the function-under-test
    cmsMLU *duplicatedMlu = cmsMLUdup(originalMlu);

    // Check if the duplication was successful and free the duplicated object
    if (duplicatedMlu != NULL) {
        cmsMLUfree(duplicatedMlu);
    }

    // Free the original cmsMLU object and the null-terminated string
    cmsMLUfree(originalMlu);
    free(nullTerminatedString);

    return 0;
}