#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern char * sam_open_mode_opts(const char *, const char *, const char *);

int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    // Ensure that the input size is large enough to split into three parts
    if (size < 3) {
        return 0;
    }

    // Calculate the lengths for each string part
    size_t len1 = size / 3;
    size_t len2 = size / 3;
    size_t len3 = size - len1 - len2;

    // Allocate memory and copy data for each string
    char *str1 = (char *)malloc(len1 + 1);
    char *str2 = (char *)malloc(len2 + 1);
    char *str3 = (char *)malloc(len3 + 1);

    if (str1 == NULL || str2 == NULL || str3 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        return 0;
    }

    memcpy(str1, data, len1);
    str1[len1] = '\0';

    memcpy(str2, data + len1, len2);
    str2[len2] = '\0';

    memcpy(str3, data + len1 + len2, len3);
    str3[len3] = '\0';

    // Call the function-under-test
    char *result = sam_open_mode_opts(str1, str2, str3);

    // Free the result if necessary
    free(result);

    // Free the allocated strings
    free(str1);
    free(str2);
    free(str3);

    return 0;
}