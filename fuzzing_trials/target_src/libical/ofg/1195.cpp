#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1195(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype) + sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the recurrence type and time type from the input data
    struct icalrecurrencetype recur;
    struct icaltimetype time;

    // Copy the data into the structures
    memcpy(&recur, data, sizeof(struct icalrecurrencetype));
    memcpy(&time, data + sizeof(struct icalrecurrencetype), sizeof(struct icaltimetype));

    // Ensure that none of the fields are null
    recur.freq = ICAL_YEARLY_RECURRENCE; // Set a default frequency
    time.year = 2023; // Set a default year

    // Call the function-under-test
    icalrecur_iterator *iterator = icalrecur_iterator_new(&recur, time);

    // Clean up if the iterator was successfully created
    if (iterator != NULL) {
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

    LLVMFuzzerTestOneInput_1195(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
