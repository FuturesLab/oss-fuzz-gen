#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>

extern "C" {

// Define a callback function to be used with icalcomponent_foreach_recurrence
void recurrence_callback_1343(const icalcomponent *comp,
                         const struct icaltime_span *span,
                         void *data) {
    // For fuzzing purposes, we do not need to do anything specific in this callback
    (void)comp;
    (void)span;
    (void)data;
}

int LLVMFuzzerTestOneInput_1343(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0; // Not enough data to form two icaltimetype structures
    }

    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract two icaltimetype structures from the input data
    struct icaltimetype start_time = *(struct icaltimetype *)data;
    struct icaltimetype end_time = *(struct icaltimetype *)(data + sizeof(struct icaltimetype));

    // Ensure that the times are valid
    start_time.is_date = 1;
    end_time.is_date = 1;

    // Call the function-under-test
    icalcomponent_foreach_recurrence(component, start_time, end_time, recurrence_callback_1343, NULL);

    // Clean up
    icalcomponent_free(component);

    return 0;
}

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

    LLVMFuzzerTestOneInput_1343(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
