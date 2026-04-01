#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Ensure that there is enough data to create two strings and an integer
    if (size < 3) {
        return 0;
    }

    // Calculate the lengths of the two strings
    size_t len1 = data[0] % (size - 2); // First string length
    size_t len2 = data[1] % (size - len1 - 1); // Second string length

    // Ensure that we have enough data for the two strings and the integer
    if (len1 + len2 + 2 > size) {
        return 0;
    }

    // Create the first string
    char str1[len1 + 1];
    memcpy(str1, data + 2, len1);
    str1[len1] = '\0'; // Null-terminate the string

    // Create the second string
    char str2[len2 + 1];
    memcpy(str2, data + 2 + len1, len2);
    str2[len2] = '\0'; // Null-terminate the string

    // Use the remaining data as the integer
    int n = (int)data[2 + len1 + len2];

    // Call the function-under-test
    int result = sqlite3_strnicmp(str1, str2, n);

    return 0;
}