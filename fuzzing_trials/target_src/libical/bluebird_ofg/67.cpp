#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libical/ical.h"

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);

    // Ensure the component is not NULL
    if (component != NULL) {
        // Call the function-under-test
        struct icaldurationtype duration = icalcomponent_get_duration(component);

        // Clean up the component

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_duration to icalproperty_set_duration
        const char xlvykokg[1024] = "qtprq";
        icalproperty* ret_icalproperty_vanew_calscale_ztdzs = icalproperty_vanew_calscale(xlvykokg);
        if (ret_icalproperty_vanew_calscale_ztdzs == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalproperty_vanew_calscale_ztdzs) {
        	return 0;
        }
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_set_duration with icalproperty_set_refreshinterval
        icalproperty_set_refreshinterval(ret_icalproperty_vanew_calscale_ztdzs, duration);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        // End mutation: Producer.APPEND_MUTATOR
        
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_67(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
