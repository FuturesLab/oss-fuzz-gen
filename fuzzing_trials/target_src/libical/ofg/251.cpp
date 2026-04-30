#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalrecurrencetype
    struct icalrecurrencetype recur;
    recur.freq = ICAL_DAILY_RECURRENCE; // Set a default recurrence frequency

    // Create an icaltimetype from the input data
    struct icaltimetype start_time;
    memcpy(&start_time, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid by setting some fields
    start_time.is_date = 0; // Set to 0 to indicate it's a date-time
    start_time.zone = icaltimezone_get_utc_timezone(); // Set timezone to UTC

    // Initialize an icalrecur_iterator with the address of recur
    icalrecur_iterator *iterator = icalrecur_iterator_new(&recur, start_time);

    // Call the function-under-test
    if (iterator != NULL) {
        bool result = icalrecur_iterator_set_start(iterator, start_time);

        // Clean up
        icalrecur_iterator_free(iterator);
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

    LLVMFuzzerTestOneInput_251(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
