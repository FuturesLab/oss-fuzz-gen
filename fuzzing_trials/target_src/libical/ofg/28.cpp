#include <cstdint>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the function parameters
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create two icaltimetype structures from the input data
    struct icaltimetype time1;
    struct icaltimetype time2;

    // Copy data to time1 and time2, ensuring they are valid
    memcpy(&time1, data, sizeof(struct icaltimetype));
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Set some valid fields in the icaltimetype structures
    time1.is_date = 0;
    time1.is_daylight = 0;
    time2.is_date = 0;
    time2.is_daylight = 0;

    // Call the function under test
    bool result = icalproperty_recurrence_is_excluded(component, &time1, &time2);

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

    LLVMFuzzerTestOneInput_28(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
