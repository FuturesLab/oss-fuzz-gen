#include <stdint.h>
#include <wchar.h>
#include <lcms2.h>
#include <string.h>

// Define the fuzzing function
int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Ensure there is enough data for key and value
    if (size < 2 * sizeof(wchar_t)) {
        return 0;
    }

    // Initialize variables
    cmsHANDLE dictHandle;
    wchar_t key[10];
    wchar_t value[10];
    cmsMLU *displayName = cmsMLUalloc(NULL, 1);
    cmsMLU *displayValue = cmsMLUalloc(NULL, 1);

    // Ensure that the displayName and displayValue are not NULL
    if (displayName == NULL || displayValue == NULL) {
        return 0;
    }

    // Calculate maximum size for key and value to prevent overflow
    size_t max_key_size = (sizeof(key) / sizeof(wchar_t)) - 1;
    size_t max_value_size = (sizeof(value) / sizeof(wchar_t)) - 1;

    // Calculate actual sizes for key and value based on input size
    size_t key_size = (size / 2) < max_key_size ? (size / 2) : max_key_size;
    size_t value_size = (size - key_size * sizeof(wchar_t)) / sizeof(wchar_t) < max_value_size ? 
                        (size - key_size * sizeof(wchar_t)) / sizeof(wchar_t) : max_value_size;

    // Copy fuzzing input into key and value, ensuring they are null-terminated
    memcpy(key, data, key_size * sizeof(wchar_t));
    key[key_size] = L'\0';

    memcpy(value, data + key_size * sizeof(wchar_t), value_size * sizeof(wchar_t));
    value[value_size] = L'\0';

    // Initialize the dictionary handle
    dictHandle = cmsDictAlloc(NULL);
    if (dictHandle == NULL) {
        cmsMLUfree(displayName);
        cmsMLUfree(displayValue);
        return 0;
    }

    // Add entries to the dictionary
    cmsDictAddEntry(dictHandle, key, value, displayName, displayValue);

    // Clean up resources
    cmsDictFree(dictHandle);
    cmsMLUfree(displayName);
    cmsMLUfree(displayValue);

    return 0;
}