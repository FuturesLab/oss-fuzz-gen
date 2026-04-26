#include <stdint.h>
#include <stddef.h>
#include <time.h> // Include time.h for time_t
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_965(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(int) + sizeof(struct icaltriggertype)) {
        return 0;
    }

    // Initialize icalproperty
    icalproperty *property = icalproperty_new(ICAL_TRIGGER_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Initialize icaltriggertype
    struct icaltriggertype trigger;
    
    // Convert the next bytes into a time_t value
    time_t trigger_time;
    memcpy(&trigger_time, data, sizeof(time_t));
    trigger.time = icaltime_from_timet_with_zone(trigger_time, 0, NULL);

    // Since 'icaltriggertype' does not have 'is_neg', we assume it's a time-based trigger
    // and set it directly without is_neg handling.

    // Call the function under test
    icalproperty_set_trigger(property, trigger);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_965(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
