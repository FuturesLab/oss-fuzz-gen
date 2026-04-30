// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_array_free at icaltimezone.c:1350:6 in icaltimezone.h
// icalenumarray_free at icalenumarray.c:132:6 in icalenumarray.h
// icalarray_free at icalarray.c:95:6 in icalarray.h
// icalarray_new at icalarray.c:27:12 in icalarray.h
// icalarray_copy at icalarray.c:60:12 in icalarray.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalarray.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalenumarray.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icaltimezone.h>

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Use the first byte to determine element size and the second byte for increment size
    size_t element_size = Data[0] % 256 + 1;  // Ensure element_size is at least 1
    size_t increment_size = Data[1] % 256;

    // Create a new icalarray
    icalarray *array = icalarray_new(element_size, increment_size);
    if (!array) return 0;

    // Attempt to copy the array
    icalarray *array_copy = icalarray_copy(array);
    if (array_copy) {
        icalarray_free(array_copy);
    }

    // Free the original array
    icalarray_free(array);

    // Create a new icalenumarray
    icalenumarray *enum_array = reinterpret_cast<icalenumarray *>(icalarray_new(element_size, increment_size));
    if (enum_array) {
        icalenumarray_free(enum_array);
    }

    // Create a new icalarray to hold timezones
    icalarray *timezone_array = icalarray_new(sizeof(icaltimezone*), increment_size);
    if (timezone_array) {
        // Free the timezone array
        icaltimezone_array_free(timezone_array);
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

        LLVMFuzzerTestOneInput_107(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    