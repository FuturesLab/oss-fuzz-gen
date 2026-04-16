#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create an htsFormat object
    if (size < sizeof(htsFormat)) {
        return 0;
    }

    // Allocate memory for htsFormat and initialize it with data
    htsFormat *format = (htsFormat *)malloc(sizeof(htsFormat));
    if (format == NULL) {
        return 0;
    }
    
    // Copy data into the htsFormat structure
    memcpy(format, data, sizeof(htsFormat));

    // Call the function-under-test
    const char *extension = hts_format_file_extension(format);

    // Use the result in some way to prevent it from being optimized away
    if (extension != NULL) {
        // Just a dummy operation to use the result
        volatile char dummy = extension[0];
        (void)dummy;
    }

    // Free allocated memory
    free(format);

    return 0;
}