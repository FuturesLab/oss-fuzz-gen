#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_505(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a valid string
    if (size < 1) return 0;

    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) return 0;

    // Create a string from the data
    char *timezone_str = (char *)malloc(size + 1);
    if (timezone_str == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(timezone_str, data, size);
    timezone_str[size] = '\0';

    // Call the function-under-test
    icaltimezone *timezone = icalcomponent_get_timezone(component, timezone_str);

    // Clean up
    free(timezone_str);
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

    LLVMFuzzerTestOneInput_505(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
