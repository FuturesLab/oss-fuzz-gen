#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Initialize a memory buffer with the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';  // Null-terminate the buffer

    // Convert the buffer to an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Ensure component is not NULL before calling the function-under-test
    if (component != nullptr) {
        // Call the function-under-test
        icalproperty *property = icalcomponent_get_current_property(component);

        // Clean up
        icalcomponent_free(component);
    }

    free(buffer);
    return 0;
}