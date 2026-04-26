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
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = static_cast<char *>(malloc(Size + 1));
    if (!inputString) {
        return 0;
    }
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Test icalparameter_new_from_string
    icalparameter *param = icalparameter_new_from_string(inputString);
    if (param) {
        // Test icalparameter_get_iana_name
        const char *iana_name = icalparameter_get_iana_name(param);
        if (iana_name) {
            std::cout << "IANA Name: " << iana_name << std::endl;
        }

        // Test icalparameter_as_ical_string_r
        char *ical_string = icalparameter_as_ical_string_r(param);
        if (ical_string) {
            std::cout << "iCal String: " << ical_string << std::endl;
            icalmemory_free_buffer(ical_string);
        }

        // Test icalparameter_set_xvalue and icalparameter_get_xvalue
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalparameter_set_xvalue with icalparameter_set_latency

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalparameter_as_ical_string_r to icalparameter_set_label

        // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from icalparameter_as_ical_string_r to icaltimezone_get_builtin_timezone_from_offset using the plateau pool
        int offset;
        // Ensure dataflow is valid (i.e., non-null)
        if (!ical_string) {
        	return 0;
        }
        icaltimezone* ret_icaltimezone_get_builtin_timezone_from_offset_bnpsb = icaltimezone_get_builtin_timezone_from_offset(offset, ical_string);
        if (ret_icaltimezone_get_builtin_timezone_from_offset_bnpsb == NULL){
        	return 0;
        }
        // End mutation: Producer.SPLICE_MUTATOR
        
        icalparameter* ret_icalparameter_new_fbtype_lbjea = icalparameter_new_fbtype(ICAL_FBTYPE_BUSYUNAVAILABLE);
        if (ret_icalparameter_new_fbtype_lbjea == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalparameter_new_fbtype_lbjea) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ical_string) {
        	return 0;
        }
        icalparameter_set_label(ret_icalparameter_new_fbtype_lbjea, ical_string);
        // End mutation: Producer.APPEND_MUTATOR
        
        icalparameter_set_latency(param, "TestValue");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
        const char *xvalue = icalparameter_get_xvalue(param);
        if (xvalue) {
            std::cout << "X-Value: " << xvalue << std::endl;
        }

        // Test icalparameter_get_xname
        const char *xname = icalparameter_get_xname(param);
        if (xname) {
            std::cout << "X-Name: " << xname << std::endl;
        }

        // Free the parameter
        icalparameter_free(param);
    }

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

    LLVMFuzzerTestOneInput_6(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
