#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>
#include <string.h>

// Fuzzing harness for hts_parse_format
int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero
    if (size == 0) {
        return 0;
    }

    // Allocate and initialize htsFormat structure
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Ensure null-terminated string for the second parameter
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    hts_parse_format(&format, input_str);

    // Free allocated memory
    free(input_str);

    return 0;
}