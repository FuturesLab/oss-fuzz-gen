#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For free()

extern "C" {
    #include <libical/ical.h> // Assuming this is the correct path for libical headers

    // Include the function-under-test
    char * icalrecurrencetype_as_string(struct icalrecurrencetype *);
}

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Ensure there is enough data to initialize the struct
    }

    // Declare and initialize a struct icalrecurrencetype
    struct icalrecurrencetype recurrence;
    
    // Initialize the struct with non-NULL values
    recurrence.freq = (enum icalrecurrencetype_frequency)(data[0] % 8); // Assuming there are 8 frequency types
    recurrence.interval = data[1];
    recurrence.count = data[2];
    recurrence.week_start = (enum icalrecurrencetype_weekday)(data[3] % 7); // Assuming 7 weekdays
    
    // Correctly initialize the 'until' field as an icaltimetype
    struct icaltimetype until_time = icaltime_null_time(); // Use a valid icaltimetype initialization
    recurrence.until = until_time;

    // Call the function-under-test
    char *result = icalrecurrencetype_as_string(&recurrence);

    // Free the result if necessary
    if (result != NULL) {
        free(result);
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

    LLVMFuzzerTestOneInput_78(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
