#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize the icaltimetype
    struct icaltimetype dtend;
    dtend.year = (size > 0) ? data[0] : 2023;  // Use the first byte or default to 2023
    dtend.month = (size > 1) ? data[1] % 12 + 1 : 1;  // Ensure month is between 1 and 12
    dtend.day = (size > 2) ? data[2] % 31 + 1 : 1;    // Ensure day is between 1 and 31
    dtend.hour = (size > 3) ? data[3] % 24 : 0;       // Ensure hour is between 0 and 23
    dtend.minute = (size > 4) ? data[4] % 60 : 0;     // Ensure minute is between 0 and 59
    dtend.second = (size > 5) ? data[5] % 60 : 0;     // Ensure second is between 0 and 59
    dtend.is_date = 0;  // Set to 0 for date-time
    dtend.zone = NULL;  // Use NULL for local time

    // Call the function-under-test
    icalcomponent_set_dtend(component, dtend);

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

    LLVMFuzzerTestOneInput_85(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
