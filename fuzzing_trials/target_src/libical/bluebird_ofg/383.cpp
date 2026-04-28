#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_383(const uint8_t *data, size_t size) {
    // Initialize a memory context for icalcomponent
    icalcomponent *component = nullptr;

    // Ensure the data size is sufficient to create a valid icalcomponent
    if (size > 0) {
        // Create a string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0'; // Null-terminate the string

        // Parse the input data into an icalcomponent
        component = icalparser_parse_string(inputData);

        // Free the input data as it's no longer needed
        free(inputData);
    }

    // If a valid icalcomponent was created, use it
    if (component != nullptr) {
        // Call the function-under-test
        char *icalString = icalcomponent_as_ical_string_r(component);

        // Free the returned string if not NULL
        if (icalString != nullptr) {
            free(icalString);
        }

        // Free the icalcomponent

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_as_ical_string_r to icaltimezone_get_builtin_timezone_from_offset
        size_t ret_icallimit_get_pauii = icallimit_get(ICAL_LIMIT_PARSE_SEARCH);
        if (ret_icallimit_get_pauii < 0){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!icalString) {
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icallimit_get to icaltime_start_doy_week
        struct icaltimetype ret_icalproperty_get_acknowledged_dyfwk = icalproperty_get_acknowledged(NULL);
        int ret_icaltime_start_doy_week_hkipc = icaltime_start_doy_week(ret_icalproperty_get_acknowledged_dyfwk, (int )ret_icallimit_get_pauii);
        if (ret_icaltime_start_doy_week_hkipc < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        icaltimezone* ret_icaltimezone_get_builtin_timezone_from_offset_bsaji = icaltimezone_get_builtin_timezone_from_offset((int )ret_icallimit_get_pauii, icalString);
        if (ret_icaltimezone_get_builtin_timezone_from_offset_bsaji == NULL){
        	return 0;
        }
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

    LLVMFuzzerTestOneInput_383(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
