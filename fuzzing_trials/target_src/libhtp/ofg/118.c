#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming bstr is a structure that holds a string and its length
typedef struct {
    char *data;
    size_t length;
} bstr;

// Mock function to create a bstr from a given data and size
static bstr *bstr_create(const uint8_t *data, size_t size) {
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
    
    return str;
}

// Mock function to free a bstr
static void bstr_free(bstr *str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

// Function-under-test
static bstr *bstr_add(bstr *str1, const bstr *str2) {
    if (str1 == NULL || str2 == NULL) return NULL;

    size_t new_length = str1->length + str2->length;
    char *new_data = (char *)malloc(new_length + 1);
    if (new_data == NULL) return NULL;

    memcpy(new_data, str1->data, str1->length);
    memcpy(new_data + str1->length, str2->data, str2->length);
    new_data[new_length] = '\0';

    bstr *result = (bstr *)malloc(sizeof(bstr));
    if (result == NULL) {
        free(new_data);
        return NULL;
    }

    result->data = new_data;
    result->length = new_length;

    return result;
}

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data to split into two parts

    // Split the input data into two parts
    size_t mid = size / 2;
    bstr *str1 = bstr_create(data, mid);
    bstr *str2 = bstr_create(data + mid, size - mid);

    if (str1 == NULL || str2 == NULL) {
        bstr_free(str1);
        bstr_free(str2);
        return 0;
    }

    // Call the function-under-test
    bstr *result = bstr_add(str1, str2);

    // Free allocated memory
    bstr_free(str1);
    bstr_free(str2);
    bstr_free(result);

    return 0;
}