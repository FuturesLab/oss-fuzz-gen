#include <string.h>
#include <sys/stat.h>
#include <cstdint> // For uint8_t
#include <cstdio>  // For printf
#include <cstdlib> // For malloc, free
#include <cstring> // For memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be used meaningfully
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the ical_string and ensure it is null-terminated
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }

    // Copy the input data to the ical_string and null-terminate it
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);

    // Perform operations on the component if it was successfully created
    if (component != NULL) {
        // Convert the component to a string
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string
            printf("%s\n", component_str);

            // Free the component string if it was allocated
            // Note: icalcomponent_as_ical_string returns a statically allocated string,
            // so we should not free it using icalmemory_free_buffer.
        }

        // Free the component
        icalcomponent_free(component);
    }

    // Free the allocated ical_string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalparser_parse_string to icalproperty_get_datetime_with_component
    icalproperty* ret_icalproperty_new_expand_vjhih = icalproperty_new_expand(64);
    if (ret_icalproperty_new_expand_vjhih == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalproperty_new_expand_vjhih) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    struct icaltimetype ret_icalproperty_get_datetime_with_component_rodix = icalproperty_get_datetime_with_component(ret_icalproperty_new_expand_vjhih, component);
    // End mutation: Producer.APPEND_MUTATOR
    
    free(ical_string);

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

    LLVMFuzzerTestOneInput_20(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
