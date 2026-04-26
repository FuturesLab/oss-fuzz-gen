#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    struct icaltimetype start_time;
    struct icaltimetype end_time;

    // Ensure the size is sufficient to extract data for the icaltimetype structures
    if (size < 16) {
        icalcomponent_free(component);
        return 0;
    }

    // Populate the icaltimetype structures with data
    start_time.year = (int)((data[0] << 8) | data[1]);
    start_time.month = (int)data[2];
    start_time.day = (int)data[3];
    start_time.hour = (int)data[4];
    start_time.minute = (int)data[5];
    start_time.second = (int)data[6];
    start_time.is_date = data[7] % 2;

    end_time.year = (int)((data[8] << 8) | data[9]);
    end_time.month = (int)data[10];
    end_time.day = (int)data[11];
    end_time.hour = (int)data[12];
    end_time.minute = (int)data[13];
    end_time.second = (int)data[14];
    end_time.is_date = data[15] % 2;

    // Call the function-under-test
    bool result = icalproperty_recurrence_is_excluded(component, &start_time, &end_time);

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

    LLVMFuzzerTestOneInput_284(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
