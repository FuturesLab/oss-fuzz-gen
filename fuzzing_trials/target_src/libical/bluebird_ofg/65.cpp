#include <sys/stat.h>
#include <string.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string for the timezone.
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data for the timezone name
    char *timezone_name = (char *)malloc(size + 1);
    if (timezone_name == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(timezone_name, data, size);
    timezone_name[size] = '\0';

    // Create a timezone using the input data
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_name);

    // If the timezone is valid, add it to the component
    if (timezone != NULL) {
        icalproperty *tz_property = icalproperty_new_tzid(timezone_name);
        if (tz_property != NULL) {
            icalcomponent_add_property(component, tz_property);
        
            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_add_property to icalcomponent_remove_component
            icalcomponent* ret_icalcomponent_new_vavailability_adlqp = icalcomponent_new_vavailability();
            if (ret_icalcomponent_new_vavailability_adlqp == NULL){
            	return 0;
            }
            // Ensure dataflow is valid (i.e., non-null)
            if (!component) {
            	return 0;
            }
            // Ensure dataflow is valid (i.e., non-null)
            if (!ret_icalcomponent_new_vavailability_adlqp) {
            	return 0;
            }
            icalcomponent_remove_component(component, ret_icalcomponent_new_vavailability_adlqp);
            // End mutation: Producer.APPEND_MUTATOR
            
}
    }

    // Free allocated resources
    free(timezone_name);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_65(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
