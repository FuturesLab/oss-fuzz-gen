#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract meaningful values
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VTODO_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract values from the data to create an icaltimetype
    int year = (int)data[0] + 1900; // Year range from 1900 to 2155
    int month = (int)(data[1] % 12) + 1; // Month range from 1 to 12
    int day = (int)(data[2] % 31) + 1; // Day range from 1 to 31
    int hour = (int)(data[3] % 24); // Hour range from 0 to 23
    int minute = (int)(data[4] % 60); // Minute range from 0 to 59
    int second = (int)(data[5] % 60); // Second range from 0 to 59

    struct icaltimetype due_time = icaltime_from_day_of_year(
        day, year);

    due_time.month = month;
    due_time.day = day;
    due_time.hour = hour;
    due_time.minute = minute;
    due_time.second = second;
    due_time.is_date = 0; // Set to 0 to indicate this is a date-time

    // Call the function-under-test
    icalcomponent_set_due(component, due_time);

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

    LLVMFuzzerTestOneInput_101(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
