#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    cmsHANDLE dictHandle;
    cmsDICTentry *entryList;
    cmsMLU *displayName, *displayValue;

    // Initialize the dictionary handle
    dictHandle = cmsDictAlloc(NULL);
    if (dictHandle == NULL) {
        return 0;
    }

    // Create display names and values
    displayName = cmsMLUalloc(NULL, 1);
    displayValue = cmsMLUalloc(NULL, 1);
    cmsMLUsetWide(displayName, "en", "US", L"Display Name 1");
    cmsMLUsetWide(displayValue, "en", "US", L"Display Value 1");

    // Add some entries to the dictionary to ensure it's not empty
    cmsDictAddEntry(dictHandle, L"Key1", L"Value1", displayName, displayValue);
    cmsDictAddEntry(dictHandle, L"Key2", L"Value2", displayName, displayValue);
    cmsDictAddEntry(dictHandle, L"Key3", L"Value3", displayName, displayValue);

    // Call the function-under-test
    entryList = (cmsDICTentry *)cmsDictGetEntryList(dictHandle);

    // Cleanup
    cmsMLUfree(displayName);
    cmsMLUfree(displayValue);
    cmsDictFree(dictHandle);

    return 0;
}