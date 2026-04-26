#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }

    // Copy data into the string and null-terminate it
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);

    // Free the string as it's no longer needed
    free(ical_string);

    // If parsing was successful, normalize the component
    if (component != NULL) {
        icalcomponent_normalize(component);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_normalize to icalproperty_get_datetime_with_component
        icalproperty* ret_icalproperty_new_transp_etrbt = icalproperty_new_transp(ICAL_TRANSP_X);
        if (ret_icalproperty_new_transp_etrbt == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalproperty_new_transp_etrbt) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!component) {
        	return 0;
        }
        struct icaltimetype ret_icalproperty_get_datetime_with_component_hvman = icalproperty_get_datetime_with_component(ret_icalproperty_new_transp_etrbt, component);
        // End mutation: Producer.APPEND_MUTATOR
        
        icalcomponent_free(component);
    }

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

    LLVMFuzzerTestOneInput_332(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
