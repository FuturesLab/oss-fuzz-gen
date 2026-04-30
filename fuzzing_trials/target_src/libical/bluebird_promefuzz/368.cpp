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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalarray.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltimezone.h"

extern "C" int LLVMFuzzerTestOneInput_368(const uint8_t *Data, size_t Size) {
    // Ensure we have enough data to work with
    if (Size < sizeof(int)) {
        return 0;
    }

    // Create a new icalarray for integers
    icalarray *intArray = icalarray_new(sizeof(int), 1);
    if (!intArray) {
        return 0;
    }

    // Append an integer from the input data
    int value;
    memcpy(&value, Data, sizeof(int));
    icalarray_append(intArray, &value);

    // Free the integer array
    icalarray_free(intArray);

    // Create an array for timezones
    icalarray *timezoneArray = icaltimezone_array_new();
    if (!timezoneArray) {
        return 0;
    }

    // Get built-in timezones
    icalarray *builtinTimezones = icaltimezone_get_builtin_timezones();
    if (builtinTimezones) {
        // Do not free the built-in timezones array as it is managed internally
    }

    // Free the timezone array
    icalarray_free(timezoneArray);

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

    LLVMFuzzerTestOneInput_368(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
