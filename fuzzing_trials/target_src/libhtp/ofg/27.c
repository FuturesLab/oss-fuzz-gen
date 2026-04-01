#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming the definition of bstr is something like this:
typedef struct {
    char *data;
    size_t len;
} bstr;

// Function under test
int bstr_index_of(const bstr *str1, const bstr *str2);

// Fuzzing harness
int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to split into two strings
    }

    // Split the input data into two parts
    size_t mid = size / 2;

    // Initialize the first bstr
    bstr str1;
    str1.data = (char *)malloc(mid + 1);
    if (str1.data == NULL) {
        return 0; // Allocation failed
    }
    memcpy(str1.data, data, mid);
    str1.data[mid] = '\0'; // Null-terminate
    str1.len = mid;

    // Initialize the second bstr
    bstr str2;
    str2.data = (char *)malloc(size - mid + 1);
    if (str2.data == NULL) {
        free(str1.data);
        return 0; // Allocation failed
    }
    memcpy(str2.data, data + mid, size - mid);
    str2.data[size - mid] = '\0'; // Null-terminate
    str2.len = size - mid;

    // Call the function under test
    int index = bstr_index_of(&str1, &str2);

    // Clean up
    free(str1.data);
    free(str2.data);

    return 0;
}