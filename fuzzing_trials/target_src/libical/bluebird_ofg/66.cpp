#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be meaningful
    if (size == 0) {
        return 0;
    }

    // Create a new VAlarm component
    icalcomponent *component = icalcomponent_new_valarm();

    // Check if the component is created successfully
    if (component != NULL) {
        // Convert the input data to a string and ensure it is null-terminated
        char *inputData = (char *)malloc(size + 1);
        if (inputData == NULL) {
            icalcomponent_free(component);
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data as an iCalendar property
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_new_from_string with icalproperty_new_organizer
        icalproperty *property = icalproperty_new_organizer(inputData);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        if (property != NULL) {
            // Add the property to the component
            icalcomponent_add_property(component, property);
        }

        // Free the allocated input data
        free(inputData);

        // Free the allocated component to avoid memory leaks
        icalcomponent_free(component);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_valarm to icalcomponent_set_parent
    icalcomponent* ret_icalparser_clean_lvubv = icalparser_clean(NULL);
    if (ret_icalparser_clean_lvubv == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalparser_clean_lvubv) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    icalcomponent_set_parent(ret_icalparser_clean_lvubv, component);
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_66(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
