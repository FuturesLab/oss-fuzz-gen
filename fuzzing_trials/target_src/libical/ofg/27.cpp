#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize icalcomponent and icaltimetype structures
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    struct icaltimetype start_time = icaltime_null_time();
    struct icaltimetype end_time = icaltime_null_time();

    // Ensure the data size is sufficient to create valid time structures
    if (size >= 16) {
        // Populate start_time and end_time with data
        start_time.year = (int16_t)((data[0] << 8) | data[1]);
        start_time.month = data[2] % 12 + 1; // Ensure month is valid (1-12)
        start_time.day = data[3] % 31 + 1;   // Ensure day is valid (1-31)
        start_time.hour = data[4] % 24;      // Ensure hour is valid (0-23)
        start_time.minute = data[5] % 60;    // Ensure minute is valid (0-59)
        start_time.second = data[6] % 60;    // Ensure second is valid (0-59)
        start_time.is_date = 0;

        end_time.year = (int16_t)((data[8] << 8) | data[9]);
        end_time.month = data[10] % 12 + 1; // Ensure month is valid (1-12)
        end_time.day = data[11] % 31 + 1;   // Ensure day is valid (1-31)
        end_time.hour = data[12] % 24;      // Ensure hour is valid (0-23)
        end_time.minute = data[13] % 60;    // Ensure minute is valid (0-59)
        end_time.second = data[14] % 60;    // Ensure second is valid (0-59)
        end_time.is_date = 0;

        // Call the function under test
        bool result = icalproperty_recurrence_is_excluded(comp, &start_time, &end_time);

        // Use the result to avoid compiler optimizations
        if (result) {
            icalcomponent_add_property(comp, icalproperty_new_comment("Recurrence is excluded"));
        }
    }

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_27(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
