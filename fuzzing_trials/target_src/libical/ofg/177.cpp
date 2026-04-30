#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers

    // Include the necessary C headers and function prototypes
    struct icaltimetype icalcomponent_get_dtend(icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    if (component == NULL) {
        return 0; // Exit if component creation fails
    }

    // Use the input data to set a property on the component
    // Here we assume the input data is a valid string for summary
    // Note: In a real-world scenario, more sophisticated parsing of `data` would be needed
    if (size > 0) {
        char *summary = (char *)malloc(size + 1);
        if (summary != NULL) {
            memcpy(summary, data, size);
            summary[size] = '\0'; // Null-terminate the string
            icalcomponent_set_summary(component, summary);
            free(summary);
        }
    }

    // Modify the input data to set a dtend property
    if (size > 16) { // Ensure there's enough data for a date-time string
        char dtend_str[17];
        memcpy(dtend_str, data, 16);
        dtend_str[16] = '\0'; // Null-terminate the string

        struct icaltimetype dtend_time = icaltime_from_string(dtend_str);
        if (!icaltime_is_null_time(dtend_time)) {
            icalcomponent_set_dtend(component, dtend_time);
        }
    }

    // Call the function-under-test
    struct icaltimetype dtend = icalcomponent_get_dtend(component);

    // Clean up the component
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

    LLVMFuzzerTestOneInput_177(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
