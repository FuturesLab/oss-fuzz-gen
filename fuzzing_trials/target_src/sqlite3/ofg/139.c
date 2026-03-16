#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Determine the split point for the two strings
    size_t split_point = size / 2;

    // Allocate memory for the strings and ensure they are null-terminated
    char *str1 = (char *)malloc(split_point + 1);
    char *str2 = (char *)malloc(size - split_point + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    memcpy(str1, data, split_point);
    str1[split_point] = '\0';

    memcpy(str2, data + split_point, size - split_point);
    str2[size - split_point] = '\0';

    // Use a fixed options value for fuzzing
    unsigned int options = 0;

    // Call the function under test
    int result = sqlite3_strlike(str1, str2, options);

    // Free allocated memory
    free(str1);
    free(str2);

    return 0;
}