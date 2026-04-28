#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_903(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype due_time;
    due_time.year = ((int)data[0] << 8) | data[1]; // Use first 2 bytes for year
    due_time.month = data[2] % 12 + 1; // Use 3rd byte for month (1-12)
    due_time.day = data[3] % 31 + 1; // Use 4th byte for day (1-31)
    due_time.hour = data[4] % 24; // Use 5th byte for hour (0-23)
    due_time.minute = data[5] % 60; // Use 6th byte for minute (0-59)
    due_time.second = data[6] % 60; // Use 7th byte for second (0-59)
    due_time.is_date = data[7] % 2; // Use 8th byte for is_date (0 or 1)
    due_time.is_daylight = 0; // Set is_daylight to 0 as a default
    due_time.zone = NULL; // Set zone to NULL

    // Call the function-under-test
    icalproperty *due_property = icalproperty_new_due(due_time);

    // Clean up
    if (due_property != NULL) {
        icalproperty_free(due_property);
    }

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

    LLVMFuzzerTestOneInput_903(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
