#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Assuming the definition of bstr is something like this
typedef struct {
    char *data;
    size_t len;
} bstr;

// Function signature provided
int bstr_index_of_mem_nocase(const bstr *str, const void *mem, size_t memlen);

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Initialize bstr
    bstr my_bstr;
    my_bstr.data = (char *)malloc(size);
    if (my_bstr.data == NULL) {
        return 0;
    }
    memcpy(my_bstr.data, data, size);
    my_bstr.len = size;

    // Initialize mem
    size_t memlen = size / 2;
    const void *mem = (const void *)(data + memlen);

    // Call the function-under-test
    int result = bstr_index_of_mem_nocase(&my_bstr, mem, memlen);

    // Cleanup
    free(my_bstr.data);

    return 0;
}