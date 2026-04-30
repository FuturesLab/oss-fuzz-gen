#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {

// Define a callback function that matches the expected signature
void recurrence_callback(const icalcomponent *comp, const struct icaltime_span *span, void *data) {
    // This is a placeholder callback function
    // In a real scenario, you might want to do something meaningful here
}

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Initialize icalcomponent and icaltimetype structures
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    struct icaltimetype start_time = icaltime_from_string("20230101T000000Z");
    struct icaltimetype end_time = icaltime_from_string("20231231T235959Z");

    // Ensure the component is not NULL before proceeding
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent_foreach_recurrence(component, start_time, end_time, recurrence_callback, NULL);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_183(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
