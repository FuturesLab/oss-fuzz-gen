#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two non-empty strings and an integer
    if (size < 3) {
        return 0;
    }

    // Determine lengths for the two strings
    size_t len1 = data[0] % (size - 2);
    size_t len2 = data[1] % (size - len1 - 1);
    int n = data[2] % (size - len1 - len2);

    // Create two strings from the data
    const char *str1 = (const char *)(data + 3);
    const char *str2 = (const char *)(data + 3 + len1);

    // Ensure null-termination
    char *buffer1 = (char *)malloc(len1 + 1);
    char *buffer2 = (char *)malloc(len2 + 1);

    if (buffer1 == NULL || buffer2 == NULL) {
        free(buffer1);
        free(buffer2);
        return 0;
    }

    memcpy(buffer1, str1, len1);
    buffer1[len1] = '\0';

    memcpy(buffer2, str2, len2);
    buffer2[len2] = '\0';

    // Call the function-under-test
    int result = sqlite3_strnicmp(buffer1, buffer2, n);

    // Clean up
    free(buffer1);
    free(buffer2);

    return 0;
}