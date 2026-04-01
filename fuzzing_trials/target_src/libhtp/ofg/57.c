#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming the bstr structure is defined as follows:
typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} bstr;

// Function under test
bstr *bstr_expand(bstr *str, size_t new_size);

// Helper function to create a bstr
bstr *create_bstr_57(const uint8_t *data, size_t size) {
    bstr *str = (bstr *)malloc(sizeof(bstr));
    if (str == NULL) return NULL;

    str->data = (char *)malloc(size + 1);
    if (str->data == NULL) {
        free(str);
        return NULL;
    }

    memcpy(str->data, data, size);
    str->data[size] = '\0';
    str->length = size;
    str->capacity = size + 1;

    return str;
}

// Helper function to free a bstr
void free_bstr_57(bstr *str) {
    if (str != NULL) {
        free(str->data);
        free(str);
    }
}

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t)) {
        return 0; // Not enough data to extract size_t for new_size
    }

    // Create a bstr from the input data
    bstr *str = create_bstr_57(data, size);
    if (str == NULL) {
        return 0;
    }

    // Extract a size_t value for new_size from the input data
    size_t new_size = *(size_t *)data;

    // Call the function under test
    bstr *expanded_str = bstr_expand(str, new_size);

    // Clean up
    free_bstr_57(expanded_str);

    return 0;
}