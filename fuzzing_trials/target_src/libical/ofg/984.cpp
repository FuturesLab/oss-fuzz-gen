#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_984(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalarray *timezones = icaltimezone_get_builtin_timezones();

    // To ensure the function is called and the result is used, we can perform a simple operation
    // such as checking the size of the array or accessing its elements.
    if (timezones != nullptr && timezones->num_elements > 0) {
        // Access the first element to ensure the array is not empty
        icaltimezone *first_timezone = static_cast<icaltimezone *>(icalarray_element_at(timezones, 0));
        if (first_timezone != nullptr) {
            // Perform a simple operation on the first timezone to ensure it's valid
            const char *tz_id = icaltimezone_get_tzid(first_timezone);
            if (tz_id != nullptr) {
                // Print the timezone ID (for debugging purposes, not necessary for fuzzing)
                // printf("Timezone ID: %s\n", tz_id);
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

    LLVMFuzzerTestOneInput_984(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
