#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libical/ical.h>
#include <string.h> // Include for memcpy

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalcompiter object
    if (size < sizeof(icalcompiter)) {
        return 0;
    }

    // Allocate memory for icalcompiter
    icalcompiter *iter = (icalcompiter *)malloc(sizeof(icalcompiter));
    if (iter == NULL) {
        return 0;
    }

    // Initialize icalcompiter with fuzz data
    memcpy(iter, data, sizeof(icalcompiter));

    // Call the function-under-test
    bool isValid = icalcompiter_is_valid(iter);

    // Free allocated memory
    free(iter);

    return 0;
}