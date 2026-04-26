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
#include <cstddef>
#include <cstring>
#include <cassert>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparser.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalerror.h"

extern "C" int LLVMFuzzerTestOneInput_338(const uint8_t *Data, size_t Size) {
    // Ensure the input data is null-terminated for string processing functions
    char *icalString = new char[Size + 1];
    memcpy(icalString, Data, Size);
    icalString[Size] = '\0';

    // Test icalparser_parse_string
    icalcomponent *component = icalparser_parse_string(icalString);
    if (component != NULL) {
        // Test icalcomponent_convert_errors
        icalcomponent_convert_errors(component);

        // Free the component
        icalcomponent_free(component);
    }

    // Check for errors and print backtrace if any
    if (*icalerror_icalerrno() != ICAL_NO_ERROR) {
        icalerror_backtrace();
    }

    // Test icalerror_error_from_string with the input string
    icalerrorenum errorEnum = icalerror_error_from_string(icalString);
    assert(errorEnum >= ICAL_NO_ERROR && errorEnum <= ICAL_UNKNOWN_ERROR);

    // Test icalcomponent_new_from_string
    component = icalcomponent_new_from_string(icalString);
    if (component != NULL) {
        // Free the component
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_strip_errors
        icalcomponent_strip_errors(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    }

    delete[] icalString;
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

    LLVMFuzzerTestOneInput_338(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
