#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1079(const uint8_t *data, size_t size) {
    // Initialize two icalcomponent pointers
    icalcomponent *comp1 = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent *comp2 = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure that comp1 and comp2 are not NULL
    if (comp1 == NULL || comp2 == NULL) {
        if (comp1 != NULL) {
            icalcomponent_free(comp1);
        }
        if (comp2 != NULL) {
            icalcomponent_free(comp2);
        }
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_parent(comp1, comp2);

    // Clean up
    icalcomponent_free(comp1);
    icalcomponent_free(comp2);

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

    LLVMFuzzerTestOneInput_1079(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
