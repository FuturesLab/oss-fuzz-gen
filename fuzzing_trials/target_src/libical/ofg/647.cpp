#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icaltimezone.h>
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_647(const uint8_t *data, size_t size) {
    // Create a dummy icaltimezone object
    icaltimezone *timezone = icaltimezone_new();

    // Ensure the timezone is not NULL
    if (timezone == NULL) {
        return 0;
    }

    // Create a dummy icalcomponent object to set properties
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Set some properties for the component to avoid NULL values
    icalcomponent_set_location(component, "Test Location");
    icalcomponent_set_uid(component, "TestUID"); // Use icalcomponent_set_uid instead

    // Call the function under test
    double longitude = icaltimezone_get_longitude(timezone);

    // Clean up the created component and timezone objects
    icalcomponent_free(component);
    icaltimezone_free(timezone, 1);

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

    LLVMFuzzerTestOneInput_647(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
