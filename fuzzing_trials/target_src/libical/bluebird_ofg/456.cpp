#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_456(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *icalString = new char[size + 1];
    memcpy(icalString, data, size);
    icalString[size] = '\0';

    // Convert the string to an icalcomponent
    icalcomponent *component = icalparser_parse_string(icalString);

    if (component != nullptr) {
        // Retrieve the first property from the component
        icalproperty *property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

        if (property != nullptr) {
            // Call the function-under-test
            int pollWinner = icalproperty_get_pollwinner(property);
        }

        // Clean up the component
        icalcomponent_free(component);
    }

    // Clean up the allocated string
    delete[] icalString;

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_456(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
