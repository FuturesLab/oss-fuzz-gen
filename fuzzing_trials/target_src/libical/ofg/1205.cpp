#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1205(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create meaningful test data
    if (size < sizeof(struct icaltimetype) + sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Extract an icalrecurrencetype from the input data
    struct icalrecurrencetype rule;
    memcpy(&rule, data, sizeof(struct icalrecurrencetype));

    // Extract an icaltimetype from the input data
    struct icaltimetype dtstart;
    memcpy(&dtstart, data + sizeof(struct icalrecurrencetype), sizeof(struct icaltimetype));

    // Initialize icalrecur_iterator with valid rule and dtstart
    icalrecur_iterator *iterator = icalrecur_iterator_new(&rule, dtstart);
    if (iterator == NULL) {
        return 0;
    }

    // Extract an icaltimetype for end_time from the input data
    struct icaltimetype end_time;
    memcpy(&end_time, data + sizeof(struct icalrecurrencetype) + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Fuzz the icalrecur_iterator_set_end function
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

    LLVMFuzzerTestOneInput_1205(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
