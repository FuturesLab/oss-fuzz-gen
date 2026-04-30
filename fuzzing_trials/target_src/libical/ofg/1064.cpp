#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_1064(const uint8_t *data, size_t size) {
    // Ensure the input size is manageable and non-zero
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Create a dummy icalcomponent to associate with the property
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        free(inputString);
        return 0;
    }

    // Call the function-under-test with a more realistic scenario
    icalproperty *property = icalproperty_new_patchdelete(inputString);
    if (property != NULL) {
        icalcomponent_add_property(component, property);
        
        // Optionally, manipulate the component to ensure deeper code paths are exercised
        // For example, convert it to a string or perform other operations
        char *componentString = icalcomponent_as_ical_string(component);
        if (componentString != NULL) {
            // Do something with componentString if needed
            free(componentString);
        }
        
        // Clean up
        icalproperty_free(property);
    }

    icalcomponent_free(component);
    free(inputString);

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

    LLVMFuzzerTestOneInput_1064(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
