#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_540(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalarray *timezones = icaltimezone_get_builtin_timezones();

    // Check if the returned array is not NULL
    if (timezones != NULL) {
        // Access the elements of the icalarray to ensure they are valid
        for (int i = 0; i < timezones->num_elements; ++i) {
            // Access each timezone entry
            icaltimezone *timezone = *(icaltimezone **)icalarray_element_at(timezones, i);
            // Perform some operations on the timezone to ensure it's valid
            const char *tzid = icaltimezone_get_tzid(timezone);
            if (tzid != NULL) {
                // Print the timezone ID (for debugging purposes)
                // In an actual fuzzing scenario, this would be removed
                // printf("Timezone ID: %s\n", tzid);
            }
        }
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

    LLVMFuzzerTestOneInput_540(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
