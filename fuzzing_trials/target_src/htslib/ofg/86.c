#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to fill an htsFormat structure
    if (size < sizeof(htsFormat)) {
        return 0;
    }

    // Allocate memory for htsFormat and copy data into it
    htsFormat *format = (htsFormat *)malloc(sizeof(htsFormat));
    if (format == NULL) {
        return 0;
    }
    memcpy(format, data, sizeof(htsFormat));

    // Call the function-under-test
    char *description = hts_format_description(format);

    // Print the description if it's not NULL
    if (description != NULL) {
        printf("Description: %s\n", description);
        free(description); // Assuming the description needs to be freed
    }

    // Free the allocated htsFormat
    free(format);

    return 0;
}