#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1068(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a valid icalrecurrencetype
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Cast the input data to a icalrecurrencetype
    struct icalrecurrencetype recurrence = *(struct icalrecurrencetype *)data;

    // Create an icalrecur_iterator from the recurrence rule
    icalrecur_iterator *iterator = icalrecur_iterator_new(&recurrence, icaltime_null_time());

    if (iterator != NULL) {
        // Call the function-under-test
        struct icaltimetype next_time = icalrecur_iterator_next(iterator);

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

    LLVMFuzzerTestOneInput_1068(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
