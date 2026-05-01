#include <sys/stat.h>
#include "libical/ical.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = NULL;
    
    // Ensure the data is not empty and null-terminate the input
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    // Copy the data and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Create a new component from the data
    component = icalcomponent_new_from_string(input);

    // Free the allocated input memory
    free(input);

    // Check if the component was created successfully
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype dtstart = icalcomponent_get_dtstart(component);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_dtstart to icalproperty_recurrence_is_excluded
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    icalproperty* ret_icalcomponent_get_current_property_kslxp = icalcomponent_get_current_property(component);
    if (ret_icalcomponent_get_current_property_kslxp == NULL){
    	return 0;
    }
    struct icaltimetype ret_icalcomponent_get_recurrenceid_rlzig = icalcomponent_get_recurrenceid(NULL);
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    bool ret_icalproperty_recurrence_is_excluded_sollz = icalproperty_recurrence_is_excluded(component, &ret_icalcomponent_get_recurrenceid_rlzig, &dtstart);
    if (ret_icalproperty_recurrence_is_excluded_sollz == 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_40(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
