// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalvalue_clone at icalvalue.c:58:12 in icalvalue.h
// icalvalue_free at icalvalue.c:785:6 in icalvalue.h
// icalvalue_new at icalvalue.c:53:12 in icalvalue.h
// icalvalue_isa at icalvalue.c:1306:16 in icalvalue.h
// icalvalue_new_from_string at icalvalue.c:780:12 in icalvalue.h
// icalvalue_as_ical_string at icalvalue.c:1197:13 in icalvalue.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalvalue.h>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a string from the input data
    std::string inputString(reinterpret_cast<const char*>(Data), Size);

    // Choose a kind based on the first byte of the input data
    icalvalue_kind kind = static_cast<icalvalue_kind>(Data[0] % ICAL_NO_VALUE);

    // Test icalvalue_new_from_string
    icalvalue *valueFromString = icalvalue_new_from_string(kind, inputString.c_str());
    if (valueFromString) {
        // Test icalvalue_clone
        icalvalue *clonedValue = icalvalue_clone(valueFromString);
        
        // Test icalvalue_isa
        icalvalue_kind isaKind = icalvalue_isa(valueFromString);

        // Test icalvalue_as_ical_string
        const char *icalString = icalvalue_as_ical_string(valueFromString);
        if (icalString) {
            std::ofstream dummyFile("./dummy_file");
            if (dummyFile.is_open()) {
                dummyFile << icalString;
                dummyFile.close();
            }
        }

        // Clean up
        icalvalue_free(valueFromString);
        if (clonedValue) {
            icalvalue_free(clonedValue);
        }
    }

    // Test icalvalue_new
    icalvalue *newValue = icalvalue_new(kind);
    if (newValue) {
        icalvalue_free(newValue);
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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_35(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    