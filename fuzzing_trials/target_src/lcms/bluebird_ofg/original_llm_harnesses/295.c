#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char key[256];
    char subkey[256];

    // Initialize handle to a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure data is large enough to fill key and subkey
    if (size < 2) {
        cmsIT8Free(handle);
        return 0;
    }

    // Copy data into key and subkey, ensuring null-termination
    size_t key_len = size / 2 < 255 ? size / 2 : 255;
    size_t subkey_len = size - key_len < 255 ? size - key_len : 255;

    memcpy(key, data, key_len);
    key[key_len] = '\0';

    memcpy(subkey, data + key_len, subkey_len);
    subkey[subkey_len] = '\0';

    // Call the function-under-test
    cmsFloat64Number result = cmsIT8GetDataDbl(handle, key, subkey);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}