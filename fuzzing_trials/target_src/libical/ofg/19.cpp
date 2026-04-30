#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data to use as a name or property
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Create a new participant component with the name
    icalcomponent *participant = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (participant != NULL) {
        icalproperty *prop = icalproperty_new_comment(name);
        if (prop != NULL) {
            icalcomponent_add_property(participant, prop);
        }

        // Clean up by freeing the allocated component
        icalcomponent_free(participant);
    }

    free(name);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_19(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
