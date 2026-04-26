#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>  // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1302(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract meaningful data
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract an icaltimetype from the input data
    struct icaltimetype dtstart;
    memcpy(&dtstart, data, sizeof(struct icaltimetype));

    // Ensure the extracted icaltimetype is valid
    dtstart.is_date = 0;  // Set a default value for is_date
    dtstart.zone = icaltimezone_get_utc_timezone();  // Set a default timezone

    // Call the function-under-test
    icalcomponent_set_dtstart(component, dtstart);

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

    LLVMFuzzerTestOneInput_1302(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
