#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_931(const uint8_t *data, size_t size) {
    // Initialize the iCalendar component
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create a string from the fuzzing data
    char *fuzz_str = (char *)malloc(size + 1);
    if (fuzz_str == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(fuzz_str, data, size);
    fuzz_str[size] = '\0';

    // Set the RELCALID property using fuzzing data
    icalproperty *relcalid_prop = icalproperty_new_relcalid(fuzz_str);
    if (relcalid_prop != NULL) {
        icalcomponent_add_property(component, relcalid_prop);
    }

    // Call the function-under-test
    const char *relcalid = icalcomponent_get_relcalid(component);

    // Check if the relcalid is not NULL and perform an operation
    if (relcalid != NULL) {
        // For example, compare it with the original fuzz string
        if (strcmp(relcalid, fuzz_str) == 0) {
            // Do something meaningful to increase code coverage
        }
    }

    // Clean up
    icalcomponent_free(component);
    free(fuzz_str);

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

    LLVMFuzzerTestOneInput_931(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
