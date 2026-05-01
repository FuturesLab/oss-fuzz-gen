#include <cstdint>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data as a string
    char *timezone_id = new char[size + 1];
    memcpy(timezone_id, data, size);
    timezone_id[size] = '\0';  // Null-terminate the string

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Add a timezone to the component to ensure there is something to retrieve
    icaltimezone *dummy_timezone = icaltimezone_get_builtin_timezone("UTC");
    if (dummy_timezone) {
        icalproperty *prop = icalproperty_new_tzid(timezone_id); // Use the fuzz input
        icalcomponent_add_property(component, prop);
    }

    // Call the function under test
    icaltimezone *timezone = icalcomponent_get_timezone(component, timezone_id);

    // Clean up
    icalcomponent_free(component);
    delete[] timezone_id;

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

    LLVMFuzzerTestOneInput_73(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
