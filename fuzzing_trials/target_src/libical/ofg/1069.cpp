#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1069(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid icalrecurrencetype
    if (size < sizeof(icalrecurrencetype)) {
        return 0;
    }

    // Allocate memory for icalrecurrencetype
    icalrecurrencetype recur;
    // Copy the data into the recur structure
    memcpy(&recur, data, sizeof(icalrecurrencetype));

    // Validate and sanitize the recur structure fields
    // Ensure the frequency is within valid range
    if (recur.freq < ICAL_SECONDLY_RECURRENCE || recur.freq > ICAL_YEARLY_RECURRENCE) {
        return 0;
    }
    // Additional validation can be added here for other fields if necessary

    // Create a dummy start time
    struct icaltimetype start = icaltime_from_day_of_year(1, 2023);

    // Create the icalrecur_iterator
    icalrecur_iterator *iterator = icalrecur_iterator_new(&recur, start);  // Pass address of recur
    if (iterator == NULL) {
        return 0;
    }

    // Call the function-under-test
    struct icaltimetype next_time = icalrecur_iterator_next(iterator);

    // Clean up
    icalrecur_iterator_free(iterator);

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

    LLVMFuzzerTestOneInput_1069(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
