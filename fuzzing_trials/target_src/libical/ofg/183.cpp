#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;
    
    if (size > 0) {
        // Create a temporary buffer to hold the input data as a string
        char *buffer = (char *)malloc(size + 1);
        if (buffer == nullptr) {
            return 0;
        }
        
        // Copy data into the buffer and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';
        
        // Parse the buffer into an icalcomponent
        component = icalparser_parse_string(buffer);
        
        // Free the temporary buffer
        free(buffer);
    }

    // Check restrictions if component is successfully created
    if (component != nullptr) {
        bool result = icalcomponent_check_restrictions(component);
        
        // Clean up the component after use
        icalcomponent_free(component);
    }

    return 0;
}