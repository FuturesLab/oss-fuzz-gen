#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming the bstr structure is defined somewhere
typedef struct {
    char *data;
    size_t length;
} bstr;

// Rename the mock implementation to avoid multiple definition conflict
bstr *mock_bstr_add_c(bstr *str, const char *suffix) {
    if (str == NULL || suffix == NULL) return NULL;
    size_t suffix_len = strlen(suffix);
    size_t new_length = str->length + suffix_len;
    char *new_data = (char *)realloc(str->data, new_length + 1);
    if (new_data == NULL) return NULL;
    memcpy(new_data + str->length, suffix, suffix_len + 1);
    str->data = new_data;
    str->length = new_length;
    return str;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize a bstr object
    bstr test_bstr;
    test_bstr.data = (char *)malloc(1);
    if (test_bstr.data == NULL) return 0;
    test_bstr.data[0] = '\0';
    test_bstr.length = 0;

    // Create a null-terminated string from the fuzzing data
    char *suffix = (char *)malloc(size + 1);
    if (suffix == NULL) {
        free(test_bstr.data);
        return 0;
    }
    memcpy(suffix, data, size);
    suffix[size] = '\0';

    // Call the mock function-under-test
    mock_bstr_add_c(&test_bstr, suffix);

    // Clean up
    free(test_bstr.data);
    free(suffix);

    return 0;
}