#include <cstdint>  // Include for uint8_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize an icaltimetype from the input data
    struct icaltimetype recurrence_id;
    memcpy(&recurrence_id, data, sizeof(struct icaltimetype));

    // Set some non-null values to ensure the icaltimetype is valid
    recurrence_id.year = 2023;
    recurrence_id.month = 10;
    recurrence_id.day = 15;
    recurrence_id.hour = 10;
    recurrence_id.minute = 30;
    recurrence_id.second = 0;
    recurrence_id.is_date = 0; // Ensure it's a date-time
    recurrence_id.zone = icaltimezone_get_utc_timezone(); // Set to UTC

    // Call the function-under-test
    icalcomponent_set_recurrenceid(component, recurrence_id);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_144(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
