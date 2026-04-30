#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_968(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype) + sizeof(struct icaltimetype)) {
        return 0;
    }

    // Cast the input data to the appropriate structures
    struct icalrecurrencetype *rule = (struct icalrecurrencetype *)data;
    struct icaltimetype *dtstart = (struct icaltimetype *)(data + sizeof(struct icalrecurrencetype));

    // Initialize an icalrecur_iterator object with the provided rule and dtstart
    icalrecur_iterator *iterator = icalrecur_iterator_new(rule, *dtstart);

    // Ensure the iterator is not NULL before proceeding
    if (iterator != NULL) {
        // Call the function-under-test
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

    LLVMFuzzerTestOneInput_968(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
