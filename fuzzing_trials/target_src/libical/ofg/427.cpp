#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_427(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid string
    if (size < 2) return 0;

    // Create a temporary string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (!ical_string) return 0;
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    if (component == NULL) {
        return 0;
    }

    // Create a property to remove
    icalproperty *property = icalproperty_new_comment("Test comment");
    if (property == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Call the function-under-test
    icalcomponent_remove_property(component, property);

    // Clean up
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_427(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
