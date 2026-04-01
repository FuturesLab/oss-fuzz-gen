#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size > 0) {
        // Convert data to a string
        std::string input(reinterpret_cast<const char*>(data), size);

        // Parse the string into an icalcomponent
        component = icalparser_parse_string(input.c_str());

        // Check if parsing was successful
        if (component != nullptr) {
            // Call the function-under-test
            int error_count = icalcomponent_count_errors(component);

            // Print the result (optional, for debugging purposes)
            std::cout << "Error count: " << error_count << std::endl;

            // Free the icalcomponent
            icalcomponent_free(component);
        }
    }

    return 0;
}