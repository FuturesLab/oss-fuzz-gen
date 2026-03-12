#include <stdint.h>
#include <stddef.h>
#include <lcms2_plugin.h>
#include <wchar.h> // Include for wchar_t

int LLVMFuzzerTestOneInput_322(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to create even one key-value pair
    }

    cmsHANDLE dictHandle = cmsDictAlloc(NULL);

    if (dictHandle != NULL) {
        // Use the input data to create keys and values
        size_t numPairs = size / 4; // Each pair needs at least 4 bytes
        for (size_t i = 0; i < numPairs; ++i) {
            wchar_t key[2] = { (wchar_t)data[i * 4], 0 };
            wchar_t value[2] = { (wchar_t)data[i * 4 + 1], 0 };

            // Add entries to the dictionary
            cmsDictAddEntry(dictHandle, key, value, NULL, NULL);
        }

        // Fuzz the function-under-test
        const cmsDICTentry *entryList = cmsDictGetEntryList(dictHandle);

        // Optionally, you can iterate over the entry list to perform further checks or operations
        const cmsDICTentry *entry = entryList;
        while (entry != NULL) {
            // Access entry->Name and entry->Value if needed
            entry = entry->Next;
        }

        // Clean up
        cmsDictFree(dictHandle);
    }

    return 0;
}