#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1283(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Create a dummy icalproperty to add to the component
    icalproperty *prop = icalproperty_new_uid("dummy-uid");
    icalcomponent_add_property(component, prop);

    // Call the function-under-test
    const char *uid = icalcomponent_get_uid(component);

    // Use the uid to prevent compiler optimizations from removing the call
    if (uid != nullptr) {
        // Do something trivial with uid
        volatile char first_char = uid[0];
        (void)first_char;
    }

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

    LLVMFuzzerTestOneInput_1283(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
