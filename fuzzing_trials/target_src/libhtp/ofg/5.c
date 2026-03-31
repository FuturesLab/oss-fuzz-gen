#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assume bstr is a structure that has been defined elsewhere
typedef struct {
    char *data;
    size_t length;
} bstr;

// Mock function for bstr_dup_ex
// Renaming the function to avoid multiple definition error
bstr *mock_bstr_dup_ex(const bstr *str, size_t start, size_t end) {
    if (str == NULL || start > end || end > str->length) {
        return NULL;
    }
    size_t new_length = end - start;
    bstr *new_bstr = (bstr *)malloc(sizeof(bstr));
    if (new_bstr == NULL) {
        return NULL;
    }
    new_bstr->data = (char *)malloc(new_length + 1);
    if (new_bstr->data == NULL) {
        free(new_bstr);
        return NULL;
    }
    memcpy(new_bstr->data, str->data + start, new_length);
    new_bstr->data[new_length] = '\0';
    new_bstr->length = new_length;
    return new_bstr;
}

// Fuzzing harness
int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to create a valid bstr
    }

    // Create a bstr from the input data
    bstr input_str;
    input_str.data = (char *)data;
    input_str.length = size;

    // Define start and end indices for mock_bstr_dup_ex
    size_t start = data[0] % size;
    size_t end = data[1] % size;
    if (start > end) {
        size_t temp = start;
        start = end;
        end = temp;
    }

    // Call the function-under-test
    bstr *result = mock_bstr_dup_ex(&input_str, start, end);

    // Clean up
    if (result != NULL) {
        free(result->data);
        free(result);
    }

    return 0;
}