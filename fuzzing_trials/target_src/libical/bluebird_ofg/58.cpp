#include <sys/stat.h>
#include <string.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        char *icalString = icalcomponent_as_ical_string_r(component);

        // Free the returned string if it's not null
        if (icalString != nullptr) {
            free(icalString);
        }

        // Free the icalcomponent
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_normalize to icalcomponent_remove_component
        icalcomponent* ret_icalcomponent_new_vlocation_zurbw = icalcomponent_new_vlocation();
        if (ret_icalcomponent_new_vlocation_zurbw == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!component) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalcomponent_new_vlocation_zurbw) {
        	return 0;
        }
        icalcomponent_remove_component(component, ret_icalcomponent_new_vlocation_zurbw);
        // End mutation: Producer.APPEND_MUTATOR
        
}

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_58(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
