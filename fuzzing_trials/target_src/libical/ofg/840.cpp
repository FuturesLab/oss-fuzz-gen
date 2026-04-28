#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_840(const uint8_t *data, size_t size) {
    // Initialize the input data as strings
    const char *data_str = reinterpret_cast<const char *>(data);
    
    // Create a dummy icalproperty and icalcomponent
    icalproperty *prop = icalproperty_new_from_string("DTSTART;TZID=America/New_York:20231010T090000");
    icalcomponent *comp = icalcomponent_new_from_string("BEGIN:VEVENT\nUID:123456\nEND:VEVENT");

    // Ensure the property and component are not NULL
    if (prop == NULL || comp == NULL) {
        if (prop != NULL) {
            icalproperty_free(prop);
        }
        if (comp != NULL) {
            icalcomponent_free(comp);
        }
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype datetime = icalproperty_get_datetime_with_component(prop, comp);

    // Clean up
    icalproperty_free(prop);
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_840(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
