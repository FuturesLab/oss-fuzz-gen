#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_578(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure data is large enough to extract a method value
    if (size < sizeof(icalproperty_method)) {
        icalcomponent_free(component);
        return 0;
    }

    // Extract a method value from the data
    icalproperty_method method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);

    // Call the function-under-test
    icalcomponent_set_method(component, method);

    // Cleanup
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

    LLVMFuzzerTestOneInput_578(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
