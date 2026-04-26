#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icaltimezone.h>
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a component
    if (size < 1) {
        return 0;
    }

    // Create a dummy icaltimezone object
    icaltimezone *timezone = icaltimezone_new();

    // Create a dummy icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);

    // Call the function-under-test
    bool result = icaltimezone_set_component(timezone, component);

    // Clean up
    icalcomponent_free(component);
    icaltimezone_free(timezone, 1); // 1 indicates to free the timezone

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

    LLVMFuzzerTestOneInput_262(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
