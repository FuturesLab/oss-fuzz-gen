#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" {
    #include "../../liblouis/liblouis.h"  // Correct path to the header file
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure we have enough data to create two non-null strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the two string parameters
    size_t mid = size / 2;

    // Create null-terminated strings for the function parameters
    char *param1 = static_cast<char*>(malloc(mid + 1));
    char *param2 = static_cast<char*>(malloc(size - mid + 1));

    if (param1 == NULL || param2 == NULL) {
        free(param1);
        free(param2);
        return 0;
    }

    memcpy(param1, data, mid);
    param1[mid] = '\0';

    memcpy(param2, data + mid, size - mid);
    param2[size - mid] = '\0';

    // Call the function-under-test
    char *result = lou_getTableInfo(param1, param2);

    // Free the allocated memory
    free(param1);
    free(param2);

    // Assuming lou_getTableInfo returns a dynamically allocated string
    // that needs to be freed. If not, remove this free.
    free(result);

    return 0;
}