#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Assuming the definition of bstr is something like this:
typedef struct {
    char *data;
    size_t len;
} bstr;

// Function signature to be fuzzed
int bstr_index_of_mem_nocase(const bstr *, const void *, size_t);

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize bstr structure
    bstr bstr_input;
    bstr_input.data = (char *)data; // Casting data to char* for bstr
    bstr_input.len = size;

    // Ensure that the size for the second parameter is not greater than the input size
    size_t mem_size = size > 0 ? size - 1 : 0;

    // Call the function-under-test
    int result = bstr_index_of_mem_nocase(&bstr_input, (const void *)data, mem_size);

    return 0;
}