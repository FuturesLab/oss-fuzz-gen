#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" int LLVMFuzzerTestOneInput_441(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create the necessary structures
    if (size < 16) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract two icaltimetype values from the input data
    icaltimetype start_time = icaltime_from_timet_with_zone((time_t)data[0], false, NULL);
    icaltimetype end_time = icaltime_from_timet_with_zone((time_t)data[8], false, NULL);

    // Extract a boolean value from the input data
    bool is_truncated = (data[15] % 2 == 0);

    // Call the function-under-test
    icaltimezone_truncate_vtimezone(component, start_time, end_time, is_truncated);

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

    LLVMFuzzerTestOneInput_441(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
