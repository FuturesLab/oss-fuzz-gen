#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume the function is declared in a header file
void janet_dynprintf(const char *prefix, FILE *file, const char *format, void *data);

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract meaningful data
    if (size < 4) return 0;

    // Split the input data into parts for each parameter
    size_t prefix_len = data[0] % (size - 3);
    size_t format_len = data[1] % (size - 3 - prefix_len);
    size_t data_offset = 2 + prefix_len + format_len;

    // Ensure we don't exceed the buffer size
    if (data_offset >= size) return 0;

    // Allocate and copy strings for prefix and format
    char *prefix = (char *)malloc(prefix_len + 1);
    char *format = (char *)malloc(format_len + 1);
    if (!prefix || !format) {
        free(prefix);
        free(format);
        return 0;
    }

    memcpy(prefix, data + 2, prefix_len);
    prefix[prefix_len] = '\0';

    memcpy(format, data + 2 + prefix_len, format_len);
    format[format_len] = '\0';

    // Use the remaining data as the data parameter
    void *dyn_data = (void *)(data + data_offset);

    // Use a temporary file to capture output
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        free(prefix);
        free(format);
        return 0;
    }

    // Call the function under test
    janet_dynprintf(prefix, temp_file, format, dyn_data);

    // Cleanup
    fclose(temp_file);
    free(prefix);
    free(format);

    return 0;
}