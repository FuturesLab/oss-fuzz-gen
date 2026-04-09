#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern char *sam_open_mode_opts(const char *, const char *, const char *);

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Ensure that there is enough data to extract three non-null strings
    if (size < 3) {
        return 0;
    }

    // Allocate memory for the three strings
    char *str1 = (char *)malloc(size / 3 + 1);
    char *str2 = (char *)malloc(size / 3 + 1);
    char *str3 = (char *)malloc(size / 3 + 1);

    // Ensure memory allocation was successful
    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        return 0;
    }

    // Copy parts of the data into the strings and null-terminate them
    memcpy(str1, data, size / 3);
    str1[size / 3] = '\0';
    memcpy(str2, data + size / 3, size / 3);
    str2[size / 3] = '\0';
    memcpy(str3, data + 2 * size / 3, size / 3);
    str3[size / 3] = '\0';

    // Call the function-under-test
    char *result = sam_open_mode_opts(str1, str2, str3);

    // Free the allocated memory
    free(str1);
    free(str2);
    free(str3);

    // Free the result if it was dynamically allocated
    free(result);

    return 0;
}