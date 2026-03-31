#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>  // Include for malloc and free

// Function-under-test declaration
int bstr_util_mem_index_of_c_nocase(const void *mem, size_t mem_size, const char *str);

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a meaningful test
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t mem_size = size / 2;
    size_t str_size = size - mem_size;

    // Create a buffer for the memory to search
    const void *mem = (const void *)data;

    // Create a buffer for the string to search for
    char *str = (char *)malloc(str_size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data + mem_size, str_size);
    str[str_size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    int result = bstr_util_mem_index_of_c_nocase(mem, mem_size, str);

    // Clean up
    free(str);

    return 0;
}