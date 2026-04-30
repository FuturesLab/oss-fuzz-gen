extern "C" {
#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
}

extern "C" int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    if (size < sizeof(time_t) + sizeof(int)) {
        return 0; // Not enough data to construct icaltriggertype
    }

    // Initialize icaltriggertype with non-NULL values
    struct icaltriggertype trigger;
    // Use the first part of the data for time and the second for duration
    trigger.time = icaltime_from_timet_with_zone(*((time_t *)(data)), 0, NULL);

    // Convert the integer to a string to use with icaldurationtype_from_string
    char duration_str[12];
    snprintf(duration_str, sizeof(duration_str), "%d", *((int *)(data + sizeof(time_t))));
    trigger.duration = icaldurationtype_from_string(duration_str);

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_trigger(trigger);

    // If the property is created, free it
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_290(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
