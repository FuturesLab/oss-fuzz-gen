#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for splitting into two strings and an integer
    if (size < 3) {
        return 0;
    }

    // Split the data into two strings and an unsigned int
    size_t str1_len = size / 3;
    size_t str2_len = size / 3;
    unsigned int options = (unsigned int)data[size - 1];

    // Allocate memory for the strings and ensure they are null-terminated
    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);

    if (str1 == NULL || str2 == NULL) {
        // Memory allocation failed
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings
    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0';

    memcpy(str2, data + str1_len, str2_len);
    str2[str2_len] = '\0';

    // Call the function-under-test
    int result = sqlite3_strlike(str1, str2, options);

    // Free the allocated memory
    free(str1);
    free(str2);

    return 0;
}