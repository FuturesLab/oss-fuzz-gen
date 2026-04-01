#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming bstr is a structure defined somewhere in the codebase
typedef struct {
    char *data;
    size_t length;
} bstr;

// Mock implementation of bstr_add_c_noex for demonstration purposes
static bstr* bstr_add_c_noex(bstr *b, const char *cstr) {
    if (b == NULL || cstr == NULL) {
        return NULL;
    }
    size_t new_length = b->length + strlen(cstr);
    char *new_data = (char *)realloc(b->data, new_length + 1);
    if (new_data == NULL) {
        return NULL;
    }
    strcat(new_data, cstr);
    b->data = new_data;
    b->length = new_length;
    return b;
}

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize bstr structure
    bstr my_bstr;
    my_bstr.data = (char *)malloc(1);
    if (my_bstr.data == NULL) {
        return 0;
    }
    my_bstr.data[0] = '\0';
    my_bstr.length = 0;

    // Convert data to a null-terminated string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        free(my_bstr.data);
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    bstr *result = bstr_add_c_noex(&my_bstr, cstr);

    // Clean up
    free(my_bstr.data);
    free(cstr);

    return 0;
}