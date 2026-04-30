#include <stdint.h>
#include <stddef.h>

// Assuming ical_invalid_rrule_handling is an enum or typedef in the actual library
extern "C" {
    typedef enum {
        ICAL_RRULE_IGNORE,
        ICAL_RRULE_LOG,
        ICAL_RRULE_EXCEPTION
    } ical_invalid_rrule_handling;

    void ical_set_invalid_rrule_handling_setting(ical_invalid_rrule_handling setting);
}

extern "C" int LLVMFuzzerTestOneInput_945(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Map the first byte of data to a valid ical_invalid_rrule_handling value
    ical_invalid_rrule_handling setting = static_cast<ical_invalid_rrule_handling>(data[0] % 3);

    // Call the function-under-test
    ical_set_invalid_rrule_handling_setting(setting);

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

    LLVMFuzzerTestOneInput_945(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
