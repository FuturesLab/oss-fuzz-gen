#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    htsFormat format;
    char *format_str;

    // Ensure that the data is null-terminated for string operations
    format_str = (char *)malloc(size + 1);
    if (format_str == NULL) {
        return 0;
    }
    memcpy(format_str, data, size);
    format_str[size] = '\0';

    // Call the function under test
    hts_parse_format(&format, format_str);

    // Clean up
    free(format_str);

    return 0;
}