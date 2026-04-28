#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a component
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Free the buffer memory
    free(buffer);

    if (component != NULL) {
        // Call the function-under-test
        struct icaltimetype dtstart = icalcomponent_get_dtstart(component);

        // Optionally, perform additional checks or operations on dtstart

        // Free the icalcomponent

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_dtstart to icalproperty_set_datemax
        icalproperty* ret_icalproperty_new_recuraccepted_oqjcx = icalproperty_new_recuraccepted((const char *)"r");
        if (ret_icalproperty_new_recuraccepted_oqjcx == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalproperty_new_recuraccepted_oqjcx) {
        	return 0;
        }
        icalproperty_set_datemax(ret_icalproperty_new_recuraccepted_oqjcx, dtstart);
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

    LLVMFuzzerTestOneInput_103(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
