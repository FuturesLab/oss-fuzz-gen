#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h"
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to create two non-null strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two strings
    size_t mid = size / 2;
    const char *firstString = reinterpret_cast<const char*>(data);
    const char *secondString = reinterpret_cast<const char*>(data + mid);

    // Ensure both strings are null-terminated
    char *firstStrCopy = static_cast<char*>(malloc(mid + 1));
    char *secondStrCopy = static_cast<char*>(malloc(size - mid + 1));

    if (firstStrCopy == nullptr || secondStrCopy == nullptr) {
        free(firstStrCopy);
        free(secondStrCopy);
        return 0;
    }

    memcpy(firstStrCopy, firstString, mid);
    firstStrCopy[mid] = '\0';

    memcpy(secondStrCopy, secondString, size - mid);
    secondStrCopy[size - mid] = '\0';

    // Call the function under test
    lou_compileString(firstStrCopy, secondStrCopy);

    // Free allocated memory
    free(firstStrCopy);
    free(secondStrCopy);

    return 0;
}