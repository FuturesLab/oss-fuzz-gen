#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Ensure we have enough data to initialize the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icalrecur_iterator and icaltimetype
    struct icalrecurrencetype recur_rule;
    struct icaltimetype start_time;

    // Copy data into start_time structure
    memcpy(&start_time, data, sizeof(struct icaltimetype));

    // Initialize recur_rule with some default values (or derive from data if needed)
    recur_rule.freq = ICAL_DAILY_RECURRENCE;
    recur_rule.interval = 1;

    icalrecur_iterator *iterator = icalrecur_iterator_new(&recur_rule, start_time);

    // Call the function-under-test
    if (iterator != NULL) {
        bool result = icalrecur_iterator_set_start(iterator, start_time);
        
        // Use the result in some way to prevent any compiler optimizations
        if (result) {
            icalrecur_iterator_free(iterator);
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

    LLVMFuzzerTestOneInput_250(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
