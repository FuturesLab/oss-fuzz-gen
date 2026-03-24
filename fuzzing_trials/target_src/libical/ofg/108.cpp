#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *vjournal = icalcomponent_new_vjournal();

    // Ensure that the created component is not NULL
    if (vjournal != NULL) {
        // Create a temporary buffer to hold the input data
        char *temp_data = new char[size + 1];
        memcpy(temp_data, data, size);
        temp_data[size] = '\0'; // Null-terminate the string

        // Parse the input data as a string
        icalcomponent *parsed_component = icalparser_parse_string(temp_data);

        // If parsing is successful, perform further operations
        if (parsed_component != NULL) {
            // Add the parsed component to vjournal
            icalcomponent_add_component(vjournal, parsed_component);

            // Serialize the component to ensure it is valid
            char *serialized = icalcomponent_as_ical_string(vjournal);
            if (serialized != NULL) {
                // Normally, you would do something with the serialized string
                // For fuzzing, we just ensure it doesn't crash
            }
        }

        // Clean up and free the components
        icalcomponent_free(vjournal);

        // Free the temporary buffer
        delete[] temp_data;
    }

    return 0;
}