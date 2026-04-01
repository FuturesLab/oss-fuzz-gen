#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "/src/libhtp/htp/bstr.h" // Correct path to bstr.h

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to split into two parts
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t bstr_size = size / 2;
    size_t char_size = size - bstr_size;

    // Initialize the bstr_t structure
    struct bstr_t bstr_input; // Use 'struct' keyword
    bstr_input.len = bstr_size;
    bstr_input.size = bstr_size;
    bstr_input.realptr = (unsigned char *)data;

    // Initialize the char array
    char char_input[char_size + 1];
    memcpy(char_input, data + bstr_size, char_size);
    char_input[char_size] = '\0'; // Null-terminate the char array

    // Call the function under test
    int result = bstr_cmp_c_nocasenorzero(&bstr_input, char_input);

    return 0;
}