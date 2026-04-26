#include <cstdint>  // Include for uint8_t
#include <cstring>  // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_714(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VTODO_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype due_time;
    memcpy(&due_time, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid
    due_time.is_date = 0; // Set to 0 to treat it as a date-time
    due_time.zone = icaltimezone_get_utc_timezone(); // Set timezone to UTC

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_714(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
