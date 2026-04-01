#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_404(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for two strings
    size_t mid = size / 2;

    // Create two null-terminated strings from the input data
    char *str1 = (char *)malloc(mid + 1);
    char *str2 = (char *)malloc(size - mid + 1);

    if (!str1 || !str2) {
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, mid);
    str1[mid] = '\0';

    memcpy(str2, data + mid, size - mid);
    str2[size - mid] = '\0';

    // Call the function-under-test
    int result = sqlite3_stricmp(str1, str2);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}