#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/bstr.h" // Correct path to the bstr header

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two parts
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t bstr_size = size / 2;
    size_t char_size = size - bstr_size;

    // Allocate memory for bstr and char array
    bstr *bstr_input = (bstr *)malloc(sizeof(bstr));
    char *char_input = (char *)malloc(char_size + 1);

    // Initialize bstr
    bstr_input->realptr = (unsigned char *)malloc(bstr_size + 1);
    memcpy(bstr_input->realptr, data, bstr_size);
    bstr_input->realptr[bstr_size] = '\0'; // Null-terminate
    bstr_input->len = bstr_size;
    bstr_input->size = bstr_size + 1; // Set the size of the buffer

    // Initialize char array
    memcpy(char_input, data + bstr_size, char_size);
    char_input[char_size] = '\0'; // Null-terminate

    // Call the function-under-test
    int result = bstr_cmp_c_nocase(bstr_input, char_input);

    // Clean up
    free(bstr_input->realptr);
    free(bstr_input);
    free(char_input);

    return 0;
}