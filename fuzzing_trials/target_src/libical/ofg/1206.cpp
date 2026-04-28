#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1206(const uint8_t *data, size_t size) {
    // Ensure there is enough data for both the iterator and the icaltimetype
    if (size < sizeof(struct icaltimetype) + sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Extract a struct icalrecurrencetype from the input data
    struct icalrecurrencetype rule;
    memcpy(&rule, data, sizeof(struct icalrecurrencetype));
    data += sizeof(struct icalrecurrencetype);

    // Extract a struct icaltimetype from the remaining input data
    struct icaltimetype dtstart;
    memcpy(&dtstart, data, sizeof(struct icaltimetype));

    // Create and initialize an icalrecur_iterator
    icalrecur_iterator *iterator = icalrecur_iterator_new(&rule, dtstart);
    if (iterator == NULL) {
        return 0;
    }

    // Extract a struct icaltimetype for end_time
    struct icaltimetype end_time;
    memcpy(&end_time, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid
    end_time.is_date = 1; // Set a non-zero value to ensure it's not NULL

    // Call the function under test
    bool result = icalrecur_iterator_set_end(iterator, end_time);

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

    LLVMFuzzerTestOneInput_1206(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
