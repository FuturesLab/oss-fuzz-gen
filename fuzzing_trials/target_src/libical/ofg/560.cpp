#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_560(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Initialize the icaltimetype
    struct icaltimetype dtend;
    dtend.year = 2023;
    dtend.month = 10;
    dtend.day = 15;
    dtend.hour = 12;
    dtend.minute = 30;
    dtend.second = 0;
    dtend.is_date = 0;
    dtend.zone = icaltimezone_get_utc_timezone();

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_560(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
