#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract three parameters
    if (size < 3) {
        return 0;
    }

    // Determine the length of the first string
    size_t len1 = data[0] % (size - 2) + 1; // Ensure len1 is at least 1 and less than size - 1

    // Determine the length of the second string
    size_t len2 = data[1] % (size - len1 - 1) + 1; // Ensure len2 is at least 1 and fits within the remaining data

    // Extract the strings
    const char *str1 = (const char *)(data + 2);
    const char *str2 = (const char *)(data + 2 + len1);

    // Ensure strings are null-terminated
    char buffer1[len1 + 1];
    char buffer2[len2 + 1];
    memcpy(buffer1, str1, len1);
    memcpy(buffer2, str2, len2);
    buffer1[len1] = '\0';
    buffer2[len2] = '\0';

    // Extract the integer parameter
    int n = data[2 + len1 + len2] % 256; // Limit the integer to a reasonable range

    // Call the function-under-test
    int result = sqlite3_strnicmp(buffer1, buffer2, n);

    // Use the result in some way to avoid optimizing away the call
    (void)result;

    return 0;
}