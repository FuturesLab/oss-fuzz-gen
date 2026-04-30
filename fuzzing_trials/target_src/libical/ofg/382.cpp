#include <stdint.h>
#include <stddef.h>

// Assuming the necessary functions and types are declared in the following header
extern "C" {
    // Since the ical.h file does not exist, we need to declare the function and type manually here
    typedef enum {
        ICAL_RRULE_IGNORE,
        ICAL_RRULE_ERROR
    } ical_invalid_rrule_handling;

    // Mock the function declaration for ical_get_invalid_rrule_handling_setting
    ical_invalid_rrule_handling ical_get_invalid_rrule_handling_setting();
}

extern "C" int LLVMFuzzerTestOneInput_382(const uint8_t *data, size_t size) {
    // Call the function-under-test
    ical_invalid_rrule_handling result = ical_get_invalid_rrule_handling_setting();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result == ICAL_RRULE_IGNORE) {
        // Do nothing, just an example of handling the result
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

    LLVMFuzzerTestOneInput_382(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
