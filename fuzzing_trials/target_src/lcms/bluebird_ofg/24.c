#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>  // Include for wchar_t
#include "lcms2.h"

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize a cmsHANDLE to a non-NULL value
    cmsHANDLE originalDict = cmsDictAlloc(NULL);
    if (originalDict == NULL) {
        return 0;
    }

    // Use the input data to add entries to the dictionary
    size_t i = 0;
    while (i + 4 <= size) { // Ensure there is enough data for key and value
        // Extract two 16-bit values from the input data as keys and values
        wchar_t key = (wchar_t)((data[i] << 8) | data[i + 1]);
        wchar_t value = (wchar_t)((data[i + 2] << 8) | data[i + 3]);
        wchar_t keyStr[2] = {key, L'\0'};
        wchar_t valueStr[2] = {value, L'\0'};

        // Add entry to the dictionary
        cmsDictAddEntry(originalDict, keyStr, valueStr, NULL, NULL);

        i += 4; // Move to the next set of key-value pairs
    }

    // Call the function-under-test
    cmsHANDLE duplicatedDict = cmsDictDup(originalDict);

    // Clean up
    if (duplicatedDict != NULL) {
        cmsDictFree(duplicatedDict);
    }
    cmsDictFree(originalDict);

    return 0;
}