#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_622(const uint8_t *data, size_t size) {
    // Initialize icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize icaltimetype
    struct icaltimetype dtstamp;
    dtstamp.year = 2023;
    dtstamp.month = 10;
    dtstamp.day = 15;
    dtstamp.hour = 10;
    dtstamp.minute = 30;
    dtstamp.second = 0;
    dtstamp.is_date = 0;
    dtstamp.zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    icalcomponent_set_dtstamp(component, dtstamp);

    // Use the input data to set a property, ensuring the input is utilized
    char *dataCopy = (char *)malloc(size + 1);
    if (dataCopy != NULL) {
        memcpy(dataCopy, data, size);
        dataCopy[size] = '\0'; // Null-terminate the string

        // Attempt to add the data as a summary to the component
        icalcomponent_set_summary(component, dataCopy);

        // Additional operations to increase code coverage
        icalcomponent_set_description(component, dataCopy);
        icalcomponent_set_location(component, dataCopy);

        // Parse the component back to string and then back to component to test parsing
        char *componentStr = icalcomponent_as_ical_string(component);
        if (componentStr != NULL) {
            icalcomponent *parsedComponent = icalparser_parse_string(componentStr);
            if (parsedComponent != NULL) {
                icalcomponent_free(parsedComponent);
            }
        }

        free(dataCopy);
    }

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

    LLVMFuzzerTestOneInput_622(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
