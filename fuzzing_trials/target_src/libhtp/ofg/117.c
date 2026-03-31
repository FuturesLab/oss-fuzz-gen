#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assume bstr is a structure representing a binary string
typedef struct {
    size_t length;
    char *data;
} bstr;

// Function-under-test
static bstr *bstr_add(bstr *dest, const bstr *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    
    // Allocate enough memory to hold the concatenated result
    char *new_data = (char *)realloc(dest->data, dest->length + src->length + 1);
    if (new_data == NULL) {
        return NULL;
    }

    // Copy the source data to the end of the destination data
    memcpy(new_data + dest->length, src->data, src->length);
    new_data[dest->length + src->length] = '\0'; // Null-terminate for safety

    // Update the destination bstr
    dest->data = new_data;
    dest->length += src->length;

    return dest;
}

// Helper function to create a bstr from data
bstr *create_bstr_117(const uint8_t *data, size_t size) {
    bstr *str = (bstr *)malloc(sizeof(bstr));
    if (str == NULL) {
        return NULL;
    }
    str->length = size;
    str->data = (char *)malloc(size + 1);
    if (str->data == NULL) {
        free(str);
        return NULL;
    }
    memcpy(str->data, data, size);
    str->data[size] = '\0'; // Null-terminate for safety
    return str;
}

// Helper function to free a bstr
void free_bstr_117(bstr *str) {
    if (str != NULL) {
        free(str->data);
        free(str);
    }
}

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to split into two bstrs
    }

    // Split the input data into two parts for two bstrs
    size_t mid = size / 2;

    // Create two bstr objects
    bstr *str1 = create_bstr_117(data, mid);
    bstr *str2 = create_bstr_117(data + mid, size - mid);

    if (str1 == NULL || str2 == NULL) {
        free_bstr_117(str1);
        free_bstr_117(str2);
        return 0;
    }

    // Call the function-under-test
    bstr *result = bstr_add(str1, str2);

    // Free the allocated memory for str2 and result only
    // str1 is the same as result if bstr_add is successful
    if (result == str1) {
        free_bstr_117(str2);
    } else {
        free_bstr_117(result);
        free_bstr_117(str1);
        free_bstr_117(str2);
    }

    return 0;
}