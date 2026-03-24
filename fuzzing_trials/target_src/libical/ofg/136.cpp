#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;
    icalparser *parser = icalparser_new();

    if (parser == nullptr) {
        return 0;
    }

    // Create a temporary string buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        icalparser_free(parser);
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Define a line generator function for the parser
    auto line_gen_func = [](char *line, size_t size, void *data) -> char* {
        char **buffer = (char **)data;
        if (*buffer == nullptr) {
            return nullptr;
        }
        char *line_copy = strdup(*buffer);
        *buffer = nullptr; // Return the buffer only once
        return line_copy;
    };

    // Set the line generator function and data for the parser
    icalparser_set_gen_data(parser, &buffer);

    // Since icalparser_set_gen_func is not a valid function, we directly use the line generator
    // function when calling icalparser_parse
    component = icalparser_parse(parser, line_gen_func);

    // Free the buffer
    free(buffer);

    if (component != nullptr) {
        // Call the function-under-test
        const char *description = icalcomponent_get_description(component);

        // Optionally, you could do something with the description here
        // For example, you could print it or check its properties

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the parser
    icalparser_free(parser);

    return 0;
}