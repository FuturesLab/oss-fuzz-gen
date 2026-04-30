#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltimezone.h"

extern "C" int LLVMFuzzerTestOneInput_331(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *inputString = (char *)malloc(Size + 1);
    if (!inputString) {
        return 0;
    }
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Test icaltimezone_get_builtin_timezone
    icaltimezone *builtinTimezone = icaltimezone_get_builtin_timezone(inputString);
    if (builtinTimezone) {
        // Test icaltimezone_copy
        icaltimezone *copiedTimezone = icaltimezone_copy(builtinTimezone);
        if (copiedTimezone) {
            // Test icaltimezone_get_latitude
            double latitude = icaltimezone_get_latitude(copiedTimezone);
            (void)latitude; // Suppress unused variable warning

            // Test icaltimezone_get_longitude
            double longitude = icaltimezone_get_longitude(copiedTimezone);

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icaltimezone_get_longitude to icalarray_element_at
            icalstrarray* ret_icalparameter_get_delegatedfrom_ntbwl = icalparameter_get_delegatedfrom(NULL);
            if (ret_icalparameter_get_delegatedfrom_ntbwl == NULL){
            	return 0;
            }
            // Ensure dataflow is valid (i.e., non-null)
            if (!ret_icalparameter_get_delegatedfrom_ntbwl) {
            	return 0;
            }
            void* ret_icalarray_element_at_qwfry = icalarray_element_at(ret_icalparameter_get_delegatedfrom_ntbwl, (size_t )longitude);
            if (ret_icalarray_element_at_qwfry == NULL){
            	return 0;
            }
            // End mutation: Producer.APPEND_MUTATOR
            
            (void)longitude; // Suppress unused variable warning

            // Free the copied timezone
            icaltimezone_free(copiedTimezone, 1);
        }
    }

    // Test icaltimezone_new
    icaltimezone *newTimezone = icaltimezone_new();
    if (newTimezone) {
        // Test icaltimezone_get_latitude
        double latitude = icaltimezone_get_latitude(newTimezone);
        (void)latitude; // Suppress unused variable warning

        // Test icaltimezone_get_longitude
        double longitude = icaltimezone_get_longitude(newTimezone);
        (void)longitude; // Suppress unused variable warning

        // Free the new timezone
        icaltimezone_free(newTimezone, 1);
    }

    // Test icaltimezone_get_builtin_timezone_from_tzid
    icaltimezone *builtinTimezoneFromTzid = icaltimezone_get_builtin_timezone_from_tzid(inputString);
    if (builtinTimezoneFromTzid) {
        // Test icaltimezone_get_latitude
        double latitude = icaltimezone_get_latitude(builtinTimezoneFromTzid);
        (void)latitude; // Suppress unused variable warning

        // Test icaltimezone_get_longitude
        double longitude = icaltimezone_get_longitude(builtinTimezoneFromTzid);
        (void)longitude; // Suppress unused variable warning
    }

    // Clean up
    free(inputString);
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

    LLVMFuzzerTestOneInput_331(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
