#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        return 0;
    }

    // Copy the input data and null-terminate it
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_get_builtin_timezone_from_tzid(tzid);

    // Clean up

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from icaltimezone_get_builtin_timezone_from_tzid to icaltime_from_timet_with_zone using the plateau pool
    // Ensure dataflow is valid (i.e., non-null)
    if (!timezone) {
    	return 0;
    }
    struct icaltimetype ret_icaltime_from_timet_with_zone_iqfxn = icaltime_from_timet_with_zone(time(NULL) + 3600, 0, timezone);
    // End mutation: Producer.SPLICE_MUTATOR
    
    free(tzid);

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
