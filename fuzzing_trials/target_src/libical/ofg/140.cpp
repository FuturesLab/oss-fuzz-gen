#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before using it as a string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Handle allocation failure
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Check if the component was created successfully
    if (component != NULL) {
        // Perform operations on the component if needed
        // For demonstration purposes, we will just free the component
        icalcomponent_free(component);
    }

    free(inputData);
    return 0;
}