#include <cstdint> // Include for uint8_t
#include <cstdio>  // Include for printf

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_625(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalarray *result = icalrecurrencetype_rscale_supported_calendars();

    // Ensure that the result is not NULL and has elements
    if (result != NULL && result->num_elements > 0) {
        // Access the first element to ensure it's valid
        const char *first_calendar = (const char *)icalarray_element_at(result, 0);
        if (first_calendar != NULL) {
            // Print the first supported calendar for debugging purposes
            printf("First supported calendar: %s\n", first_calendar);
        }
    }

    // Clean up if necessary
    if (result != NULL) {
        icalarray_free(result);
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

    LLVMFuzzerTestOneInput_625(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
