#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure there is enough data for two strings and an unsigned int
    if (size < 3) {
        return 0;
    }

    // Find the positions to split the input data into two strings
    size_t pos1 = data[0] % (size - 2) + 1;
    size_t pos2 = data[1] % (size - pos1 - 1) + pos1 + 1;

    // Create null-terminated strings from the input data
    char str1[pos1 + 1];
    char str2[pos2 - pos1 + 1];

    memcpy(str1, data, pos1);
    str1[pos1] = '\0';

    memcpy(str2, data + pos1, pos2 - pos1);
    str2[pos2 - pos1] = '\0';

    // Use the remaining byte as the unsigned int option
    unsigned int options = data[pos2];

    // Call the function under test
    sqlite3_strlike(str1, str2, options);

    return 0;
}