#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Function-under-test signature
int cmsstrcasecmp(const char *s1, const char *s2);

// Fuzzing harness
int LLVMFuzzerTestOneInput_374(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for two strings
    char *str1 = (char *)malloc(size / 2 + 1);
    char *str2 = (char *)malloc(size / 2 + 1);

    // Ensure allocation was successful
    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, size / 2);
    str1[size / 2] = '\0';

    memcpy(str2, data + size / 2, size / 2);
    str2[size / 2] = '\0';

    // Call the function-under-test
    int result = cmsstrcasecmp(str1, str2);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}