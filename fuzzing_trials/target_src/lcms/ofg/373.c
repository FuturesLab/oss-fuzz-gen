#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

// Function-under-test
int cmsstrcasecmp(const char *s1, const char *s2);

// Fuzzing harness
int LLVMFuzzerTestOneInput_373(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for two strings and null terminators
    if (size < 2) return 0;

    // Calculate lengths for the two strings
    size_t len1 = size / 2;
    size_t len2 = size - len1;

    // Allocate memory for the strings and ensure they are null-terminated
    char *str1 = (char *)malloc(len1 + 1);
    char *str2 = (char *)malloc(len2 + 1);

    if (str1 == NULL || str2 == NULL) {
        // If memory allocation fails, clean up and exit
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, len1);
    str1[len1] = '\0';

    memcpy(str2, data + len1, len2);
    str2[len2] = '\0';

    // Call the function-under-test
    int result = cmsstrcasecmp(str1, str2);

    // Print the result (optional, for debugging purposes)
    printf("Result: %d\n", result);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}