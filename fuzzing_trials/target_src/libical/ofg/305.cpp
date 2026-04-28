extern "C" {
    #include <libical/ical.h>
}
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Ensure there's at least one byte of data
    }

    // Initialize the icalrecurrence structure
    icalrecurrencetype recur;
    recur.freq = static_cast<icalrecurrencetype_frequency>(data[0] % ICAL_SECONDLY_RECURRENCE); // Assuming ICAL_SECONDLY_RECURRENCE is the max value
    recur.interval = 1;
    recur.count = 10;
    recur.until = icaltime_null_time();

    // Create a start time for the recurrence
    struct icaltimetype start = icaltime_from_string("20230101T000000Z");

    // Create an icalrecur_iterator
    icalrecur_iterator *iterator = icalrecur_iterator_new(&recur, start);
    if (!iterator) {
        return 0; // If iterator creation fails, exit
    }

    // Iterate through the recurrence
    struct icaltimetype next_time;
    while (!icaltime_is_null_time((next_time = icalrecur_iterator_next(iterator)))) {
        // Process the next_time if needed
    }

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

    LLVMFuzzerTestOneInput_305(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
