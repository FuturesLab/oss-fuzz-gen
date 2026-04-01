#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_404(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Find a midpoint to split the data into two strings
    size_t midpoint = size / 2;

    // Create two null-terminated strings
    char *str1 = (char *)malloc(midpoint + 1);
    char *str2 = (char *)malloc(size - midpoint + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, midpoint);
    str1[midpoint] = '\0';

    memcpy(str2, data + midpoint, size - midpoint);
    str2[size - midpoint] = '\0';

    // Call the function-under-test
    int result = sqlite3_stricmp(str1, str2);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}