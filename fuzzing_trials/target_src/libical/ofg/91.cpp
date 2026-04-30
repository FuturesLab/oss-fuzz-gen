#include <stdint.h>
#include <stdlib.h>

// Wrap the necessary includes and declarations with extern "C"
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    struct icaldurationtype duration;

    // Ensure the data is large enough to fill the duration fields
    if (size < sizeof(struct icaldurationtype)) {
        icalcomponent_free(component);
        return 0;
    }

    // Populate the duration fields using the input data
    duration.is_neg = data[0] % 2; // 0 or 1
    duration.weeks = data[1];
    duration.days = data[2];
    duration.hours = data[3];
    duration.minutes = data[4];
    duration.seconds = data[5];

    // Call the function-under-test
    icalcomponent_set_duration(component, duration);

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

    LLVMFuzzerTestOneInput_91(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
