extern "C" {
    #include <libical/ical.h>
    #include <stddef.h>
    #include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput_624(const uint8_t *data, size_t size) {
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_comment("Sample comment");
    icalcomponent_add_property(component, property);

    icalproperty *iter = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

    if (iter != NULL) {
        // Do something with iter if needed
    }

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

    LLVMFuzzerTestOneInput_624(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
