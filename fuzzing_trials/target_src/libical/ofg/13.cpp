#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure there is enough data to process
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        icalproperty_method method = icalcomponent_get_method(component);
        
        // Optionally, print the method for debugging purposes
        std::cout << "Method: " << method << std::endl;

        // Free the parsed component
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
