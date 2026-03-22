#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    plist_t plist = plist_new_string(inputString);

    // Clean up
    free(inputString);
    if (plist != NULL) {
        plist_free(plist);
    }

    return 0;
}