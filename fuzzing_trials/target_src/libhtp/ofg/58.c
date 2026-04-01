#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming bstr is a structure that looks something like this:
typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} bstr;

// Function to be tested
bstr *bstr_expand(bstr *str, size_t new_size);

// Helper function to create a bstr
bstr *create_bstr_58(const char *initial_data, size_t initial_capacity) {
    bstr *str = (bstr *)malloc(sizeof(bstr));
    if (str == NULL) return NULL;

    size_t data_length = strlen(initial_data);
    str->data = (char *)malloc(initial_capacity);
    if (str->data == NULL) {
        free(str);
        return NULL;
    }

    strncpy(str->data, initial_data, data_length);
    str->length = data_length;
    str->capacity = initial_capacity;

    return str;
}

// Helper function to free a bstr
void free_bstr_58(bstr *str) {
    if (str != NULL) {
        free(str->data);
        free(str);
    }
}

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there's at least some data

    // Create a bstr with some initial data and capacity
    bstr *str = create_bstr_58("initial", 10);
    if (str == NULL) return 0;

    // Use the first byte of data to determine the new size for expansion
    size_t new_size = (size_t)data[0];

    // Call the function-under-test
    bstr *expanded_str = bstr_expand(str, new_size);

    // Clean up
    free_bstr_58(expanded_str);

    return 0;
}