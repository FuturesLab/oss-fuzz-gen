#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define the bstr structure before using it
typedef struct {
    char *data;
    size_t len;
    size_t capacity;
} bstr;

// Adjust the size of the bstr structure
// Making this function static to avoid multiple definition errors
static void bstr_adjust_size(bstr *str, size_t new_size) {
    if (new_size > str->capacity) {
        char *new_data = (char *)realloc(str->data, new_size);
        if (new_data) {
            str->data = new_data;
            str->capacity = new_size;
        }
    }
    str->len = new_size < str->capacity ? new_size : str->capacity - 1;
    str->data[str->len] = '\0'; // Ensure null-termination
}

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize a bstr structure
    bstr str;
    str.capacity = size > 0 ? size : 1; // Ensure capacity is at least 1
    str.len = size > 0 ? size - 1 : 0;  // Ensure len is less than capacity
    str.data = (char *)malloc(str.capacity);
    
    if (str.data == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy data into the bstr's data, ensuring null-termination
    if (size > 0) {
        memcpy(str.data, data, str.len);
        str.data[str.len] = '\0'; // Null-terminate
    }

    // Call the function under test with a variety of sizes
    for (size_t new_size = 0; new_size <= size + 10; new_size++) {
        bstr_adjust_size(&str, new_size);
    }

    // Clean up
    free(str.data);

    return 0;
}