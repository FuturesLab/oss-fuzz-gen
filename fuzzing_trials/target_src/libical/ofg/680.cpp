#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_680(const uint8_t *data, size_t size) {
    // Initialize the icalproperty and icaldurationtype structures
    icalproperty *property = icalproperty_new(ICAL_ESTIMATEDDURATION_PROPERTY);
    struct icaldurationtype duration;

    // Ensure the data size is sufficient to fill the icaldurationtype structure
    if (size >= sizeof(struct icaldurationtype)) {
        // Copy data into the duration structure
        memcpy(&duration, data, sizeof(struct icaldurationtype));
    } else {
        // If not enough data, set default values for the duration
        const char *default_duration_str = "PT1H"; // Default to 1 hour in ISO 8601 format
        duration = icaldurationtype_from_string(default_duration_str);
    }

    // Call the function-under-test
    icalproperty_set_estimatedduration(property, duration);

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

    LLVMFuzzerTestOneInput_680(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
