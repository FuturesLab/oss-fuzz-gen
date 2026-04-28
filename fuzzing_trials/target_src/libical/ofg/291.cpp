#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icaltriggertype
    if (size < sizeof(struct icaltriggertype)) {
        return 0;
    }

    // Initialize the icaltriggertype structure
    struct icaltriggertype trigger;

    // Assuming the first part of data is for time, convert it to icaltimetype
    if (size >= sizeof(struct icaltimetype)) {
        trigger.time = *((struct icaltimetype *)data);
        data += sizeof(struct icaltimetype);
        size -= sizeof(struct icaltimetype);
    } else {
        // If not enough data for time, initialize with default values
        trigger.time = icaltime_null_time();
    }

    // Assuming the remaining data is for duration
    if (size >= sizeof(struct icaldurationtype)) {
        trigger.duration = *((struct icaldurationtype *)data);
    } else {
        // If not enough data for duration, initialize with default values
        trigger.duration = icaldurationtype_from_string("PT0S");
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_trigger(trigger);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_291(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
