#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Convert the input data to a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data as an iCalendar component
    icalparser *parser = icalparser_new();
    icalparser_set_gen_data(parser, input);

    // Define a line generator function
    auto line_gen_func = [](char *s, size_t size, void *d) -> char* {
        strncpy(s, (char *)d, size);
        return s;
    };

    icalcomponent *component = icalparser_parse(parser, line_gen_func);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    icalparser_free(parser);
    free(input);

    return 0;
}