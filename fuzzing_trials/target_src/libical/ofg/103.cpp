#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {

// A simple callback function to be used with icalcomponent_foreach_tzid
void tzid_callback(icalparameter *param, void *data) {
    // This is where you would handle the parameter and data
    // For fuzzing purposes, we can leave it empty or log the parameter
}

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Initialize a memory zone for icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a dummy data pointer
    void *user_data = static_cast<void*>(const_cast<uint8_t*>(data));

    // Call the function-under-test
    icalcomponent_foreach_tzid(component, tzid_callback, user_data);

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

    LLVMFuzzerTestOneInput_103(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
