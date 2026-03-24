#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a string from the input data
        std::string inputData(reinterpret_cast<const char*>(data), size);

        // Parse the string to create an icalcomponent
        component = icalparser_parse_string(inputData.c_str());
    }

    // Call the function-under-test
    if (component != nullptr) {
        icalcomponent *innerComponent = icalcomponent_get_inner(component);

        // Clean up
        icalcomponent_free(component);
    }

    return 0;
}