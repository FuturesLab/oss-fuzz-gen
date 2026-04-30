#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated to be used as a string
    char *x_name = (char *)malloc(size + 1);
    if (x_name == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(x_name, data, size);
    x_name[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_x_name(component, x_name);

    // Additional function calls to increase code coverage
    // Set some properties to the component
    icalproperty *summary_prop = icalproperty_new_summary("Fuzzing Summary");
    icalproperty *description_prop = icalproperty_new_description("Fuzzing Description");
    icalcomponent_add_property(component, summary_prop);
    icalcomponent_add_property(component, description_prop);

    // Retrieve properties to ensure they are set
    const char *summary = icalcomponent_get_summary(component);
    const char *description = icalcomponent_get_description(component);

    // Check if properties are correctly set
    if (summary && description) {
        // Do something with the retrieved properties if needed
    }

    // Clean up
    free(x_name);
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

    LLVMFuzzerTestOneInput_14(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
