#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two strings and an unsigned int
    if (size < 3) {
        return 0;
    }

    // Calculate lengths for the two strings
    size_t len1 = size / 3;
    size_t len2 = size / 3;
    
    // Ensure the lengths do not exceed the size
    if (len1 + len2 + sizeof(unsigned int) > size) {
        return 0;
    }

    // Allocate and copy the first string
    char *str1 = (char *)malloc(len1 + 1);
    if (str1 == NULL) {
        return 0;
    }
    memcpy(str1, data, len1);
    str1[len1] = '\0';

    // Allocate and copy the second string
    char *str2 = (char *)malloc(len2 + 1);
    if (str2 == NULL) {
        free(str1);
        return 0;
    }
    memcpy(str2, data + len1, len2);
    str2[len2] = '\0';

    // Extract the unsigned int from the remaining data
    unsigned int esc = *(unsigned int *)(data + len1 + len2);

    // Call the function-under-test
    int result = sqlite3_strlike(str1, str2, esc);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}