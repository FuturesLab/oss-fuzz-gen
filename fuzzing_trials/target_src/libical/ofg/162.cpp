#include <iostream>
#include <libical/ical.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a component
    if (size < 1) return 0;

    // Create a string from the input data
    char *inputData = new char[size + 1];
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data to create an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);
    delete[] inputData;

    if (component == nullptr) return 0;

    // Initialize the iterator with the component
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function under test
    icalcomponent *result = icalcompiter_deref(&iter);

    // Clean up
    icalcomponent_free(component);

    return 0;
}