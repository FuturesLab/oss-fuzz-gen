#include <stdint.h>
#include <stddef.h>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure data size is sufficient to create a valid string
    if (size < 2) return 0;

    // Create a temporary null-terminated string from the input data
    char *ical_str = new char[size + 1];
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Initialize an icalcomponent from the string
    icalcomponent *component = icalparser_parse_string(ical_str);
    if (component == NULL) {
        delete[] ical_str;
        return 0;
    }

    // Create a dummy icalproperty to remove
    icalproperty *property = icalproperty_new_comment("Dummy comment");
    if (property == NULL) {
        icalcomponent_free(component);
        delete[] ical_str;
        return 0;
    }

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcomponent_remove_property(component, property);

    // Clean up
    icalcomponent_free(component);
    delete[] ical_str;

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

    LLVMFuzzerTestOneInput_56(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
